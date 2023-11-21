
typedef struct inputode{
        input num;
        struct inputode* next;
} inputode;

typedef struct char_node{
        char num;
        struct char_node* next;
} char_node;


typedef inputode* Big_stack;

typedef char_node* char_stack;



void init_Big_stack(Big_stack *s);
void init_char_stack(char_stack *s);

void push_input(Big_stack *head, input num);
void push_char(char_stack *head, char num);

input pop_input(Big_stack *head);
char pop_char(char_stack *head);

input peek_input(Big_stack st);
char peek_char(char_stack st);

int isEmpty_input(Big_stack st);
int isEmpty_char(char_stack st);
