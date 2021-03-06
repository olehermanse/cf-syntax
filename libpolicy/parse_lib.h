#ifndef PARSE_LIB_H
#define PARSE_LIB_H

#include <stdbool.h>  // bool
#include <stdio.h>    // FILE
#include <stack.h>    // Stack
#include <sequence.h> // Seq

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define RST "\033[0m"

typedef struct PolicyFile {
    Seq *bodies;
    char *name;
} PolicyFile;

typedef struct Parser {
    char *current_line;
    const char *current_token;
    size_t column_number;
    size_t line_number;
    size_t errors;
    PolicyFile *policy;
    Stack *stack;
    FILE *output;
    size_t output_column;
    bool insert_empty_line;
} Parser;

PolicyFile *ParseFileStream(FILE *input_file, const char *name, FILE *output);
bool LexFileStream(FILE *input_file, const char *name);
PolicyFile *ParseFile(const char *path);

Parser* NewParser(const char *filename, FILE *output);
void DestroyParser(Parser *p);
PolicyFile *CloseParser(Parser *p);
PolicyFile *NewPolicyFile(const char *filename);
void DestroyPolicyFile(PolicyFile *policy_file);

void ParserBeginBody(Parser *p);
void ParserSetBodyType(Parser *p, const char *type);
void ParserSetBodyName(Parser *p, const char *name);
void ParserEndBody(Parser *p);

void ParserBeginAttribute(Parser *parser, const char *string);
void ParserEndAttribute(Parser *parser);

void ParserAddString(Parser *parser, const char *string);

void ParserBeginList(Parser *parser);
void ParserEndList(Parser *parser);

#endif
