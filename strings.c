#include "monty.h"

void print_char(stack_t **, unsigned int);
void print_str(stack_t **, unsigned int);

/**
 * print_char - Prints the Ascii value.
 * @stack: Pointer to a pointer pointing to top node of the stack.
 * @line_number: Interger representing the line number of of the opcode.
 */
void print_char(stack_t **stack, unsigned int line_number)
{
	int aski;

	if (stack == NULL || *stack == NULL)
		string_err(11, line_number);
	aski = (*stack)->n;
	if (aski < 0 || aski > 127)
		string_err(10, line_number);
	printf("%c\n", aski);
}

/**
 * print_str - Prints a string.
 * @stack: Pointer to a pointer pointing to top node of the stack.
 * @ln: Interger representing the line number of of the opcode.
 */
void print_str(stack_t **stack, __attribute__((unused)) unsigned int ln)
{
	int aski;
	stack_t *temp;

	if (stack == NULL || *stack == NULL)
	{
		printf("\n");
		return;
	}
	temp = *stack;
	while (temp != NULL)
	{
		aski = temp->n;
		if (aski <= 0 || aski > 127)
			break;
		printf("%c", aski);
		temp = temp->next;
	}
	printf("\n");
}
