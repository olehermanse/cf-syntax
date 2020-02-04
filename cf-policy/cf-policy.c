#include <parse_lib.h>
#include <string_lib.h> // StringMatchesOption()
#include <file_lib.h>   // safe_fopen()
#include <policy.h>     // Body

static void RenderPolicy(PolicyFile *policy, const char *filename)
{
    assert(policy != NULL);

    stdout = safe_fopen(filename, "w");
    size_t length = SeqLength(policy->bodies);
    for (int i = 0; i < length; ++i)
    {
        Body *body = SeqAt(policy->bodies, i);
        PrintBody(body);
        if (i != (length - 1))
        {
            printf("\n");
        }
    }
}

int main(int argc, const char *const *argv)
{
    // Remove executable name from argc/argv:
    argc -= 1;
    argv += 1;

    // Parse remaining command line args:
    bool print_tokens = false;
    const char *filename = NULL;
    const char *render_file = NULL;
    while (argc > 0)
    {
        if (StringMatchesOption(argv[0], "--render", "-r"))
        {
            if (argc < 2 || argv[1][0] == '-')
            {
                printf("Error: --render requires an output file name!\n");
                return 1;
            }
            argc -= 1;
            argv += 1;
            render_file = argv[0];
        }
        else if (StringMatchesOption(argv[0], "--tokens", "-t"))
        {
            print_tokens = true;
        }
        else
        {
            if (filename != NULL)
            {
                printf("Error: Too many file names!\n");
                return 1;
            }
            filename = argv[0];
        }
        argc -= 1;
        argv += 1;
    }

    // Open file if specified:
    FILE *file_stream = stdin;
    if (filename != NULL)
    {
        file_stream = safe_fopen(filename, "r");
    }
    int ret = 0;
    // Lex / Parse file:
    if (print_tokens)
    {
        // Only print tokens, don't check syntax:
        // (Uses only the flex generated lexer, not the yacc parser grammar)
        ret = LexFileStream(file_stream, filename) ? 0 : 1;
    }
    else
    {
        PolicyFile *policy = ParseFileStream(file_stream, filename);
        // Parse file, check syntax according to yacc grammar:
        if (policy != NULL)
        {
            printf("Syntax check: " GREEN "OK" RST "\n");

            RenderPolicy(policy, render_file);
        }
        else
        {
            printf("Syntax check: " RED "FAILED" RST "\n");
            ret = 1;
        }
        DestroyPolicyFile(policy);
    }
    return ret;
}
