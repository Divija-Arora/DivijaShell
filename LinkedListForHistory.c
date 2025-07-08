#include "linkedListForHistory.h"
#include <signal.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

struct historyList *head_of_list = NULL;
struct historyList *curr_of_list = NULL;

struct historyList *create_list_of_history(char *line, bool validity)
{
    struct historyList *ptr = (struct historyList *)malloc(sizeof(struct historyList));
    if (NULL == ptr)
    {
        printf("\n Node creation of History List failed \n");
        return NULL;
    }
    ptr->command = line;
    ptr->isValid = validity;
    ptr->next = NULL;

    head_of_list = ptr;
    curr_of_list = ptr;
    return ptr;
}

void print_list_of_history(historyList *head_of_historylist)
{
    struct historyList *ptr = head_of_historylist;
    int length = 0;
    printf("-----Commands marked with " ANSI_COLOR_RED "RED" ANSI_COLOR_RESET " were invalid and those marked with " ANSI_COLOR_BLUE "BLUE" ANSI_COLOR_RESET " were valid-----");
    printf("\n =============== History =============== \n\n");
    while (ptr != NULL)
    {
        length++;
        if (ptr->isValid)
        {
            printf(ANSI_COLOR_BLUE);
            printf(" %d - %s", length, ptr->command);
            printf(ANSI_COLOR_RESET);
        }
        else
        {
            printf(ANSI_COLOR_RED);
            printf(" %d - %s", length, ptr->command);
            printf(ANSI_COLOR_RESET);
        }

        ptr = ptr->next;
    }
    printf("\n ======================================================= \n\n");
    return;
}

struct historyList *add_to_list_of_history(char *line, bool validity)
{
    if (NULL == head_of_list)
    {
        return (create_list_of_history(line, validity));
    }

    struct historyList *ptr = (struct historyList *)malloc(sizeof(struct historyList));
    if (NULL == ptr)
    {
        return NULL;
    }
    ptr->command = line;
    ptr->isValid = validity;
    ptr->next = NULL;
    curr_of_list->next = ptr;
    curr_of_list = ptr;
    return ptr;
}
