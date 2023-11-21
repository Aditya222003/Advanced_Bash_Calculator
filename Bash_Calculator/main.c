#include "main_suppl_funs.h"

int cont;

int solve_expr() {
    cont = 0;
    list inp;
    get_info info;
    init(&inp);
    init_info(&info);

    char ch;
    while ((ch = getchar()) != '\n') {
      append(&inp, ch);
    }
    append(&inp, '\0');

    char_stack s;
    Big_stack val;
    init_Big_stack(&val);
    init_char_stack(&s);

    input result, temp, op1, op2;
    init_num(&temp);
    init_num(&result);

    char operan, c;
    int unary_neg = 0;
    get_token(&info, &inp);
    if(info.token == 'q')
    {
			printf("Thank You ! \n");
			exit(1);
    }
    
    if(info.token == '\0') 
    {
        printf("0 \n");
        return 0;
    }
   
   else if(info.token == '<')
   {
    	if (info.next_token == 'O')
    	{
    	
			get_token(&info, &inp);
			get_token(&info, &inp);

			char outbase[3];
			outbase[0] = info.token;
	
			if(isdigit(info.next_token))
			{
				get_token(&info, &inp);
				outbase[1] = info.token;
				outbase[2] = '\0';
			}
		
			else
				outbase[1] = '\0';
		
		info.out_base = atoi(outbase);
		
		get_token(&info, &inp);
		
		info.token = '+';
		get_token(&info, &inp);
	}
	else if(info.next_token != 'I') {
		printf("Syntax Error.\n");
		printf("TYPE: token 'O' or 'I' is necessary after '<'.\n");
		return 0;
	}
}
    handle_tokens(&info, &inp, &val);
    if(cont)
    	return 0; 

    while(info.token != '\0') 
    {
	   
	    c = info.token;

	   
            if(isdigit(c)){
	       insertInEnd(&temp, c - '0');
	   
               if(! isdigit(info.next_token)) {
		  
		    if(info.unary_neg) {
			    neg(&temp);
			    info.unary_neg = 0;
		    }
		   
		    push_input(&val, temp);
		    init_num(&temp);
	       }
            }

	    
            else if( c == '('){
                push_char(&s,'(');
		
		if (! isOperator(info.token = info.prev_token)){
			printf("Syntax error.\n");
			error(info.token, '(');
		}
	    }
	   
        else if(c == ')')
        {
            while(!isEmpty_char(s) && peek_char(s)!= '(')
            {
                op2 = pop_input(&val);
                op1 = pop_input(&val);
		        operan = pop_char(&s);
                push_input(&val, eval(&op1, &op2, operan));
            }
		    if(peek_char(s) == '(')
                pop_char(&s);
		  
            else
            {
			    printf("Syntax Error.\n");
		    	printf("TYPE: closing brackets are not matched with opening bracket.\n");
			    return 0;
		    }
        }
	    
        else 
        {
		    if (isOperator(c)) 
            {
                if(isEmpty_char(s))
                    push_char(&s, c);
                else 
                {
			        while(!isEmpty_char(s) && precedence(peek_char(s)) >= precedence(c) && !info.r_ass)
                    {
				    op2 = pop_input(&val);
				    op1 = pop_input(&val);
				    operan = pop_char(&s);
				    push_input(&val, eval(&op1, &op2, operan));
                    }
                push_char(&s, c);
                info.r_ass = 0;
                }
            }
		    else 
            {
		    printf("Syntax Error.\n");
		    printf("Type: Wrong operator or symbol '%c'\n", c);
			return 0;
		    }
        }
	  
	    get_token(&info, &inp);
	    handle_tokens(&info, &inp, &val);
	    if(cont)
	    	return 0;
    }
    while(!isEmpty_char(s))
    {
	    op2 = pop_input(&val);
        op1 = pop_input(&val);
     	operan = pop_char(&s);
	if(operan == '(')
	{
		printf("Syntax Error.\nTYPE: Opening brackets are not matched with closing bracket.\n");
		return 0;
	}
       	push_input(&val, eval(&op1, &op2, operan));
    }
    result = changeBase(pop_input(&val), info.out_base);
    display(result);
    return 0;
}

int main() {
    int cont = 0;
    printf("\n\n==================================================================\n");
    printf("                      WELCOME TO BASH CALCULATOR          \n");
    printf("==================================================================\n");
    printf("                                       - By Aditya Raul COEP(CS)'25\n");
    printf("\n\nInstructions :\n");
    printf("----------------");
    printf("\n1- Enter the Expression in a single line ");
    printf("\n2- Press ' ENTER ' for result ");
    printf("\n3- Press ' q ' to Exit the calculator ");
    printf("\n\n Enter Your Expression = \n");
    while(1) {
	
	solve_expr();
		
    }
}



