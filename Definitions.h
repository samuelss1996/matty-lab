#define SYMBOL_TYPE_VARIABLE 300
#define SYMBOL_TYPE_FUNCTION 301
#define SYMBOL_TYPE_CONSTANT 302

#define WELCOME_MESSAGE_FILE "txt/welcome.txt"
#define HELP_MESSAGE_FILE "txt/help.txt"

#define READABILITY_SYMBOL_NOT_FOUND 400
#define READABILITY_SYMBOL_FUNCTION 401
#define READABILITY_VARIABLE 402
#define READABILITY_CONSTANT 403

#define ASSIGNABILITY_SYMBOL_FUNCTION 500
#define ASSIGNABILITY_SYMBOL_CONSTANT 501
#define ASSIGNABILITY_ASSIGNABLE 502

#define CALLABILITY_SYMBOL_NOT_FOUND 600
#define CALLABILITY_SYMBOL_NOT_FUNCTION 601
#define CALLABILITY_ARGUMENT_COUNT_MISMATCH 602
#define CALLABILITY_CALLABLE 603

#define SYMBOLS_HASH_TABLE_CAPACITY 500

#define EXIT_CODE_SUCCESS 0
#define EXIT_CODE_WRONG_ARGUMENTS (-1000)
#define EXIT_CODE_UNABLE_TO_OPEN_FILE (-1001)
#define EXIT_CODE_UNABLE_TO_OPEN_KEYWORDS_DB (-1003)

#define ANSI_COLOR_ERROR "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"