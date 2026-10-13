#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bvm.h"

int assemble_basm_to_bvm(char* input_file, char* output_file);
int assemble_sh_to_basm(char* input_file, char* output_file);

int main(int argc, char** argv)
{
    int status;
    if (argc < 3) {   // минимальное количество аргументов – 2 (программа + режим + файл)
        printf("Usage:\n"
               "\tbvmc -sa <.sh>   [-o <.basm>]\n"
               "\tbvmc -ab <.basm> [-o <.bvm> ]\n"
               "\tbvmc -sb <.sh>   [-o <.bvm> ]\n"
               "\tbvmc -e  <.bvm>\n"
               "\tbvmc -se <.sh>\n"
               "\tbvmc -ae <.basm>\n"
              );
        return 1;
    }

    char *mode = argv[1];
    char *input_file = argv[2];
    char *output_file = NULL;

    // ----- РЕЖИМ -e (просто выполнить .bvm) -----
    if (strcmp(mode, "-e") == 0) {
        if (argc != 3) {
            fprintf(stderr, "Error: mode -e expects exactly one argument (<.bvm>)\n");
            return 1;
        }
        const char *in_ext = strrchr(input_file, '.');
        if (!in_ext || strcmp(in_ext, ".bvm") != 0) {
            fprintf(stderr, "Error: for mode -e input file must have .bvm extension\n");
            return 1;
        }
        printf("Executing %s\n", input_file);
        status = execute_bvm(input_file);
        if (status != 0) return 1;
        return status;
    }

    // ----- РЕЖИМ -se (скомпилировать и выполнить .sh без сохранения .bvm) -----
    if (strcmp(mode, "-se") == 0) {
        if (argc != 3) {
            fprintf(stderr, "Error: mode -se expects exactly one argument (<.sh>)\n");
            return 1;
        }
        const char *in_ext = strrchr(input_file, '.');
        if (!in_ext || strcmp(in_ext, ".sh") != 0) {
            fprintf(stderr, "Error: for mode -se input file must have .sh extension\n");
            return 1;
        }
        printf("Compiling and executing %s\n", input_file);

        // Создаём временные файлы (в реальном коде использовать mkstemp или tmpnam)
        char temp_basm[] = "tempXXXXXX.basm";
        char temp_bvm[]  = "tempXXXXXX.bvm";
        // здесь нужно создать уникальные имена, для примера – заглушка
        status = assemble_sh_to_basm(input_file, temp_basm);
        if (status != 0) goto se_error;
        status = assemble_basm_to_bvm(temp_basm, temp_bvm);
        if (status != 0) goto se_error;
        status = execute_bvm(temp_bvm);
        if (status != 0) goto se_error;
        remove(temp_basm);
        remove(temp_bvm);
        return 0; 
    se_error:
        remove(temp_basm);
        remove(temp_bvm);
        return 1;
    }

    // ----- РЕЖИМ -ae (собрать и выполнить .basm без сохранения .bvm) -----
    if (strcmp(mode, "-ae") == 0) {
        if (argc != 3) {
            fprintf(stderr, "Error: mode -ae expects exactly one argument (<.basm>)\n");
            return 1;
        }
        const char *in_ext = strrchr(input_file, '.');
        if (!in_ext || strcmp(in_ext, ".basm") != 0) {
            fprintf(stderr, "Error: for mode -ae input file must have .basm extension\n");
            return 1;
        }
        printf("Assembling and executing %s\n", input_file);
        char temp_bvm[] = "tempXXXXXX.bvm";
        status = assemble_basm_to_bvm(input_file, temp_bvm);
        if (status != 0) goto ae_error;
        status = execute_bvm(temp_bvm);
        if (status != 0) goto ae_error;
        remove(temp_bvm);
        return 0;
    ae_error:
        remove(temp_bvm);
        return 1;
    }

    // ----- РЕЖИМЫ, ТРЕБУЮЩИЕ ВЫХОДНОГО ФАЙЛА (-sa, -ab, -sb) -----
    if (argc != 3 && argc != 5) {
        fprintf(stderr, "Error: for modes -sa/-ab/-sb need 1 or 2 arguments (input and optional -o output)\n");
        return 1;
    }

    if (strcmp(mode, "-sa") != 0 && strcmp(mode, "-ab") != 0 && strcmp(mode, "-sb") != 0) {
        fprintf(stderr, "Error: unknown mode '%s'\n", mode);
        return 1;
    }

    // Проверка расширения входного файла
    const char *in_ext = strrchr(input_file, '.');
    if (!in_ext) {
        fprintf(stderr, "Error: input file has no extension\n");
        return 1;
    }

    if ((strcmp(mode, "-sa") == 0 || strcmp(mode, "-sb") == 0)) {
        if (strcmp(in_ext, ".sh") != 0) {
            fprintf(stderr, "Error: for mode %s input file must have .sh extension\n", mode);
            return 1;
        }
    } else if (strcmp(mode, "-ab") == 0) {
        if (strcmp(in_ext, ".basm") != 0) {
            fprintf(stderr, "Error: for mode -ab input file must have .basm extension\n");
            return 1;
        }
    }

    // Обработка выходного файла
    if (argc == 5) {
        if (strcmp(argv[3], "-o") != 0) {
            fprintf(stderr, "Error: expected '-o' before output file\n");
            return 1;
        }
        output_file = argv[4];

        const char *out_ext = strrchr(output_file, '.');
        if (!out_ext) {
            fprintf(stderr, "Error: output file has no extension\n");
            return 1;
        }

        if (strcmp(mode, "-sa") == 0 && strcmp(out_ext, ".basm") != 0) {
            fprintf(stderr, "Error: for mode -sa output file must have .basm extension\n");
            return 1;
        }
        if (strcmp(mode, "-ab") == 0 && strcmp(out_ext, ".bvm") != 0) {
            fprintf(stderr, "Error: for mode -ab output file must have .bvm extension\n");
            return 1;
        }
        if (strcmp(mode, "-sb") == 0 && strcmp(out_ext, ".bvm") != 0) {
            fprintf(stderr, "Error: for mode -sb output file must have .bvm extension\n");
            return 1;
        }
    } else { // argc == 3 – генерируем имя выходного файла по умолчанию
        char *default_out = malloc(strlen(input_file) + 5);
        if (!default_out) {
            fprintf(stderr, "Memory allocation error\n");
            return 1;
        }
        strcpy(default_out, input_file);
        char *dot = strrchr(default_out, '.');
        if (dot) *dot = '\0';
        if (strcmp(mode, "-sa") == 0) {
            strcat(default_out, ".basm");
        } else { // -ab или -sb
            strcat(default_out, ".bvm");
        }
        output_file = default_out;
    }

    // Вызов соответствующих функций
    if (strcmp(mode, "-sa") == 0) {
        printf("Assembling %s to %s\n", input_file, output_file);
        status =  assemble_sh_to_basm(input_file, output_file);
    } else if (strcmp(mode, "-ab") == 0) {
        printf("Converting %s to %s\n", input_file, output_file);
        status =  assemble_basm_to_bvm(input_file, output_file);
    } else { // -sb
        printf("Compiling %s to %s\n", input_file, output_file);
        status =  assemble_sh_to_basm(input_file, output_file);
        if (status == 0)
            status =  assemble_basm_to_bvm(input_file, output_file);
    }

    if (argc == 3) {
        free(output_file);
    }

    return status;
}

// заглушки (остаются как были)
int assemble_sh_to_basm(char* input_file, char* output_file) { return 0; }

