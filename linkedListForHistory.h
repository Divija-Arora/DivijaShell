#include "utilities.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct historyList
{
	char* command;
	bool isValid;
	struct historyList* next;
} historyList;

struct historyList* create_list_of_history(char*, bool);
struct historyList* add_to_list_of_history(char*, bool);
void print_list_of_history(historyList*);