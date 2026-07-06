#include "lexer.h"

char keywords_found[100][50];
char identifiers_found[100][50];
char numbers_found[100][50];
char operators_found[100][10];
char symbols_found[100][10];

int kw_count = 0;
int id_count = 0;
int num_count = 0;
int op_count = 0;
int sym_count = 0;

char *keywords[] =
{
    "int",
    "float",
    "char",
    "if",
    "else",
    "while",
    "for",
    "return",
    "void"
};

int is_keyword(char *word)
{
    int n = sizeof(keywords) / sizeof(keywords[0]);

    for(int i = 0; i < n; i++)
    {
        if(strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int is_identifier(char *word)
{
    if(!(isalpha(word[0]) || word[0] == '_'))
        return 0;

    for(int i = 1; word[i] != '\0'; i++)
    {
        if(!(isalnum(word[i]) || word[i] == '_'))
            return 0;
    }

    return 1;
}

int is_number(char *word)
{
    for(int i = 0; word[i] != '\0'; i++)
    {
        if(!isdigit(word[i]))
            return 0;
    }

    return 1;
}

int is_operator(char ch)
{
    return (ch == '+' || ch == '-' ||
            ch == '*' || ch == '/' ||
            ch == '=');
}

int is_symbol(char ch)
{
    return (ch == ';' || ch == ',' ||
            ch == '(' || ch == ')' ||
            ch == '{' || ch == '}');
}

int is_string(char *word)
{
    int len = strlen(word);

    if(len >= 2 && word[0] == '"' && word[len - 1] == '"')
        return 1;

    return 0;
}

void print_token(char *lexeme, int token_type)
{
    switch(token_type)
    {
        case KEYWORD:
            strcpy(keywords_found[kw_count++], lexeme);
            break;

        case IDENTIFIER:
            strcpy(identifiers_found[id_count++], lexeme);
            break;

        case NUMBER:
            strcpy(numbers_found[num_count++], lexeme);
            break;

        case OPERATOR:
            strcpy(operators_found[op_count++], lexeme);
            break;

        case SYMBOL:
            strcpy(symbols_found[sym_count++], lexeme);
            break;
    }
}

void analyze_file(FILE *fp)
{
    char ch;
    char token[100];
    int i;

    while((ch = fgetc(fp)) != EOF)
    {
        if(isalpha(ch) || ch == '_')
        {
            i = 0;

            while(isalnum(ch) || ch == '_')
            {
                token[i++] = ch;
                ch = fgetc(fp);
            }

            token[i] = '\0';

            if(ch != EOF)
                ungetc(ch, fp);

            if(is_keyword(token))
                print_token(token, KEYWORD);
            else if(is_identifier(token))
                print_token(token, IDENTIFIER);
        }

        else if(isdigit(ch))
        {
            i = 0;

            while(isdigit(ch))
            {
                token[i++] = ch;
                ch = fgetc(fp);
            }

            token[i] = '\0';

            if(ch != EOF)
                ungetc(ch, fp);

            print_token(token, NUMBER);
        }

        else if(is_operator(ch))
        {
            token[0] = ch;
            token[1] = '\0';

            print_token(token, OPERATOR);
        }

        else if(is_symbol(ch))
        {
            token[0] = ch;
            token[1] = '\0';

            print_token(token, SYMBOL);
        }
    }

    printf("----------------------------------------\n");
    printf("         LEXICAL ANALYZER OUTPUT\n");
    printf("----------------------------------------\n");

    printf("\nKeywords:\n");
    for(i = 0; i < kw_count; i++)
        printf("%s\n", keywords_found[i]);

    printf("\nIdentifiers:\n");
    for(i = 0; i < id_count; i++)
        printf("%s\n", identifiers_found[i]);

    printf("\nNumbers:\n");
    for(i = 0; i < num_count; i++)
        printf("%s\n", numbers_found[i]);

    printf("\nOperators:\n");
    for(i = 0; i < op_count; i++)
        printf("%s\n", operators_found[i]);

    printf("\nSymbols:\n");
    for(i = 0; i < sym_count; i++)
        printf("%s\n", symbols_found[i]);

    printf("\n----------------------------------------\n");
    printf("Summary\n");
    printf("----------------------------------------\n");

    printf("Keywords     : %d\n", kw_count);
    printf("Identifiers  : %d\n", id_count);
    printf("Numbers      : %d\n", num_count);
    printf("Operators    : %d\n", op_count);
    printf("Symbols      : %d\n", sym_count);
}