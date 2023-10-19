#include "monty.h"

void open_file(char *file_name);
void read_file(FILE *);
int parse_line(char *buff, int line_n, int format);
void find_func(char *, char *, int, int);
void call_fun(op_func, char *, char *, int, int);

/**
 * open_file - opens a file
 * @file_name: the file namepath
 * Return: void
 */

void open_file(char *file_name)
{
	FILE *_file = fopen(file_name, "r");

	if (file_name == NULL || _file == NULL)
		err(2, file_name);
	read_file(_file);
	fclose(_file);
}


/**
 * read_file - reads a file
 * @_file: pointer to file descriptor
 * Return: void
 */

void read_file(FILE *_file)
{
	int line_n, format = 0;
	char *buff = NULL;
	size_t l = 0;

	for (line_n = 1; getline(&buff, &l, _file) != -1; line_n++)
	{
		format = parse_line(buff, line_n, format);
	}
	free(buff);
}


/**
 * parse_line - Separates each line into tokens to determine
 * which function to call
 * @buff: line from the file
 * @line_n: line number
 * @format:  storage format. If 0 Nodes will be entered as a stack.
 * if 1 nodes will be entered as a queue.
 * Return: Returns 0 if the opcode is stack. 1 if queue.
 */

int parse_line(char *buff, int line_n, int format)
{
	char *opcode, *val;
	const char *dlim = "\n ";

	if (buff == NULL)
		err(4);
	opcode = strtok(buff, dlim);
	if (opcode == NULL)
		return (format);
	val = strtok(NULL, dlim);
	if (strcmp(opcode, "stack") == 0)
		return (0);
	if (strcmp(opcode, "queue") == 0)
		return (1);
	find_func(opcode, val, line_n, format);
	return (format);
}

/**
 * find_func - find the appropriate function for the opcode
 * @opcode: opcode
 * @val: argument of opcode
 * @format:  storage format. If 0 Nodes will be entered as a stack.
 * @ln: line number
 * if 1 nodes will be entered as a queue.
 * Return: void
 */
void find_func(char *opcode, char *val, int ln, int format)
{
	int i;
	int flag;

	instruction_t func_list[] = {
		{"push", add_to_stack},
		{"pall", print_stack},
		{"pint", print_top},
		{"pop", pop_top},
		{"nop", nop},
		{"swap", swap_nodes},
		{"add", add_nodes},
		{"sub", sub_nodes},
		{"div", div_nodes},
		{"mul", mul_nodes},
		{"mod", mod_nodes},
		{"pchar", print_char},
		{"pstr", print_str},
		{"rotl", rotl},
		{"rotr", rotr},
		{NULL, NULL}
	};
	if (opcode[0] == '#')
		return;
	for (flag = 1, i = 0; func_list[i].opcode != NULL; i++)
	{
		if (strcmp(opcode, func_list[i].opcode) == 0)
		{
			call_fun(func_list[i].f, opcode, val, ln, format);
			flag = 0;
		}
	}
	if (flag == 1)
		err(3, ln, opcode);
}


/**
 * call_fun - Calls the required function.
 * @func: Pointer to the function that is about to be called.
 * @op: string representing the opcode.
 * @val: string representing a numeric val.
 * @ln: line numeber for the instruction.
 * @format: Format specifier. If 0 Nodes will be entered as a stack.
 * if 1 nodes will be entered as a queue.
 */
void call_fun(op_func func, char *op, char *val, int ln, int format)
{
	stack_t *new;
	int flag, i;

	flag = 1;
	if (strcmp(op, "push") == 0)
	{
		if (val != NULL && val[0] == '-')
		{
			val = val + 1;
			flag = -1;
		}
		if (val == NULL)
			err(5, ln);
		for (i = 0; val[i] != '\0'; i++)
		{
			if (isdigit(val[i]) == 0)
				err(5, ln);
		}
		new = create_node(atoi(val) * flag);
		if (format == 0)
			func(&new, ln);
		if (format == 1)
			add_to_queue(&new, ln);
	}
	else
		func(&head, ln);
}
