#include "num.h"

int symall = 0, syfr = 0;

/* to init head structure of big number*/
void init_num(input *num) {
	num->size = 0;
	/*init with +ve no*/
	num->sign = 0; 
	num->head = num->tail = NULL;
}

/*changes the sign of the number*/
void neg(input *num) {
	/*if number is negative*/
	if(num->sign)
		num->sign = 0;
	/*if number is positive*/
	else
		num->sign = 1;
}

/* to remove leading zeros e.g. 005 = 5*/
void rem_lead_zeros(input *num) {
    node* temp = num->head;
    node* follow;
    int count = 0;
    input new;
    init_num(&new);

    /*traverse till we get digit other than 0 or 
     * end of linked list*/
    while (temp && temp->data == 0) {
	follow = temp;
        temp = temp->next;
	/*free the leading zeros*/
	free(follow);
	syfr++;
	count++;
    }
    /*if temp = end of linked list i.e. number is 0*/
    if(temp == NULL) {
	    *num = new;
	    return;
    }
    /*change head structure*/
    temp->prev = NULL;
    num->head = temp;
    num->size -= count;
    return;
}

void destroy(input *num)  {
    node* temp = num->head;
    node* follow = NULL;

    input new;
    init_num(&new);
    *num = new;
    
    /*free all the nodes till we reach end of list*/
    while (temp) {
        follow = temp;
        temp = temp->next;
        free(follow);
	syfr++;
    }
    return;
}


/*To display the number.*/
void display(input num) {
    node* temp = num.head;
    if(num.size == 0) {
	    printf("0\n");
	    return;
    }
    if(num.sign)
	    printf("-");
    while (temp) {
	/*if node data less than 10 , i.e. 0-9*/
	if (temp->data < 10)
        	printf("%c", temp->data + '0');
	/* base > 10
	 * if node data greater or equal t 10 , 
	 * print corresponding character value*/
	else
		printf("%c", (temp->data - 10) + 'A');
        temp = temp->next;
    }
    printf("\n");
    return;
}


// To insert at the beginning of the list 
void insertInFront(input *num, int value) {
    node* temp = (node*)malloc(sizeof(node));
    symall++;
    /*malloc successfull*/
    if(temp) {
    	temp->next = temp->prev = NULL;
	temp->data = value;
    }
    /*malloc unsuccessfull*/
    else return;
	
    /*if list is empty*/
    if (num->head == NULL){
        num->head = num->tail = temp;}
    else {
        num->head->prev = temp;
        temp->next = num->head;
        num->head = temp;
    }
    /*incrise size by one*/
    num->size++;
}

// To insert in the end 
void insertInEnd(input *num, int value) {
    node* temp = (node*)malloc(sizeof(node));
    symall++;
    /*malloc successfull*/
    if(temp) {
        temp->next = temp->prev = NULL;
        temp->data = value;
    }
    /*malloc unsuccessfull*/
    else return;

    /*if list is empty*/
    if (num->tail == NULL)
        num->head = num->tail = temp;
    else {
        num->tail->next = temp;
        temp->prev = num->tail;
        num->tail = temp;
    }
    /*increase size by one*/
    num->size++;
}

// Returns the number of digits 
int length(input num) {
    return num.size;
}


// This compares the two numbers and returns  
// true or 1 when a is greater 
int compare(input a, input b) {
    /*remove leading zeros of both numbers*/
    rem_lead_zeros(&a);
    rem_lead_zeros(&b);

    input a1 = a;
    input b1 = b;

    int rev = 0;
    /*if numbers have unequal sign*/
    if(a1.sign != b1.sign) {
	    if(b1.sign)
		    return 1;
	    else
		    return 2;
    }
    /*if both numbers are negative*/
    else if(a1.sign)
	    rev = 1;

    /* size of both no are unequal
     * if 1st no size is greater than 2nd no size, 1st no is greater 
     * and similar for 2nd no*/
    if (a1.size != b1.size) {
	if(! rev)
        	return ((a1.size > b1.size) ? 1 : 2);
	else 
		return ((a1.size > b1.size) ? 2 : 1);
    }
    /* size of both no are equal
     * compare from left to right */
    else {
        while (a1.head != NULL && b1.head != NULL) {
            if (a1.head->data > b1.head->data) {
		if(! rev)
                	return 1;
	    	else
			return 2;
	    }
            else if (a1.head->data < b1.head->data) {
		if(! rev)
                	return 2;
		else 
			return 1;
	    }
            else {
                a1.head = a1.head->next;
                b1.head = b1.head->next;
            }
        }
	/*both numbers are equal*/
        return 0;
    }
}



/*Uses simple addition method that we
follow using carry*/
input add(input *a, input *b) {
    rem_lead_zeros(a);
    rem_lead_zeros(b);

    input a1 = *a;
    input b1 = *b;

    int c = 0, s;
    input addition;
    init_num(&addition);

    /*if both numbers have unequal sign*/
    if(a1.sign != b1.sign) {
            if(a1.sign == 0) {
                neg(&b1);
		/*result = a-b*/
                return sub(&a1, &b1);
            }
            else {
		/*result = b-a*/
                neg(&a1);
                return sub(&b1, &a1);
            }
    }
    /*addition result sign = common sign of both numbers*/
    else
        addition.sign = a1.sign;

    /*add from right to left*/
    while (a1.tail != NULL || b1.tail != NULL) {
        if (a1.tail != NULL && b1.tail != NULL) {
	    /*add with carry*/
            s = ((a1.tail->data) + (b1.tail->data) + c) % 10;
	    /*calculate carry*/
            c = ((a1.tail->data) + (b1.tail->data) + c) / 10;
	    /*traverse next digits*/
            a1.tail = a1.tail->prev;
            b1.tail = b1.tail->prev;
        }
	/*if size of 2nd no is greater than 1st*/
        else if (a1.tail == NULL && b1.tail != NULL) {
            s = ((b1.tail->data) + c) % 10;
            c = ((b1.tail->data) + c) / 10;
            b1.tail = b1.tail->prev;
        }
	/*if size of 1st no is greater than 2nd*/
        else if (a1.tail != NULL && b1.tail == NULL) {
            s = ((a1.tail->data) + c) % 10;
            c = ((a1.tail->data) + c) / 10;
            a1.tail = a1.tail->prev;
        }
	/*insert s in addition*/
        insertInFront(&addition, s);
    }

    // Inserting last carry
    if (c != 0)
        insertInFront(&addition, c);

    return addition;
}


// Normal subtraction is done by borrowing 
input sub(input *a, input *b) {
    rem_lead_zeros(a);
    rem_lead_zeros(b);
    input a1 = *a;
    input b1 = *b;

    int c = 0, s, rev = 0;
    input subtraction, temp;
    init_num(&subtraction);

    /*if both numbers have unequal sign*/
    if(a1.sign != b1.sign) {
            if(a1.sign == 0) {
                neg(&b1);
		/*result = a+b*/
                return add(&a1, &b1);
            }
            else {
                neg(&b1);
		/*result = (-a)+(-b)*/
                return add(&a1, &b1);
            }
    }
    /*if both numbers are negative, convert both no to positive 
     * perform sub and change result sign at last*/
    else if(a1.sign &&  b1.sign){
            neg(&a1);
            neg(&b1);
            rev = 1;
    }

    int cmp = compare(a1, b1);
    /*if both numbers are equal, result = 0*/
    if(! cmp)
            return subtraction;
    /*if second no is greater than 1st,
     * swap structure of both no so that 1st no will always be greater*/
    if(cmp == 2) {
	    /*give -ve sign to result*/
	    neg(&subtraction);
            temp = a1;
            a1 = b1;
            b1 = temp;
    }
    
    while (a1.tail != NULL || b1.tail != NULL) {
        if (a1.tail != NULL && b1.tail != NULL) {
	    /*if 1st numbers digit is greater than 2nd*/
            if ((a1.tail->data) + c >= (b1.tail->data)) {
                s = ((a1.tail->data) + c - (b1.tail->data));
                c = 0;
            }
	    /*if 2nd numbers digit is greater than 1st, (borrow)*/
            else {
                s = ((a1.tail->data) + c + 10 - (b1.tail->data));
                c = -1;
            }
	    /*traverse next*/
            a1.tail = a1.tail->prev;
            b1.tail = b1.tail->prev;
        }
	/*if size of 1st no is greater than 2nd*/
        else if (a1.tail != NULL && b1.tail == NULL) {
            if (a1.tail->data >= 1) {
                s = ((a1.tail->data) + c);
                c = 0;
            }
	    /*if digit is 0*/
            else {
		/*if borrow*/
                if (c != 0) {
                    s = ((a1.tail->data) + 10 + c);
		    /*borrow from next*/
                    c = -1;
                }
                else
                    s = a1.tail->data;
            }
            a1.tail = a1.tail->prev;
        }
	/*insert s in result*/
        insertInFront(&subtraction, s);
    }
    /*remove leading zeros of result*/
    rem_lead_zeros(&subtraction);
    /*give appropriate sign to result*/
    if(rev) {
        neg(&subtraction);
        return subtraction;
    }
    return subtraction;
}




// Normal multiplication is used i.e. in one to all way 
input mult(input *l, input *m) {
    rem_lead_zeros(l);
    rem_lead_zeros(m);
    input a1 = *l;
    input b1 = *m;

    int sign = 0;
    /*if unequal sign, result is -ve*/
    if(a1.sign != b1.sign)
	    sign = 1;

    int k = 0, i, count = 0;
    input multiplican, temp, a, b;
    input tmpfree;
    init_num(&multiplican);
    init_num(&temp);
  
    /*if any number is zero , result is zero*/
    if(a1.size == 0 || b1.size == 0)
	   return multiplican;

    b = b1;
    /*one digit of 2nd no multiply to all digits of 1st no*/
    while (b.tail != NULL) {
        int c = 0, s = 0;
	a = a1;
	/*multiply to each digit of 1st no*/
        while (a.tail != NULL) {
            s = ((a.tail->data) * (b.tail->data) + c) % 10;
	    /*calculate carry*/
            c = ((a.tail->data) * (b.tail->data) + c) / 10;
	    /*insert s in temp list(input)*/
            insertInFront(&temp, s);
            a.tail = a.tail->prev;
        }
	/*insert if last carry*/
        if (c != 0)
            insertInFront(&temp, c);

	/*insert appropriate zeros at end*/
        for (i = 0; i < k; i++)
            insertInEnd(&temp, 0);

	tmpfree = multiplican;
	/*each time add temp in multiplican result*/
	multiplican = add(&multiplican, &temp);
	destroy(&tmpfree);

        k++;
	/*take next digit for multiplication*/
        b.tail = b.tail->prev;
	destroy(&temp);
    }
    /*give appropriate sign*/
    multiplican.sign = sign;
    return multiplican;
}



// normal division.
input division(input *l, input *m) {
    rem_lead_zeros(l);
    rem_lead_zeros(m);
    input a1 = *l;
    input b1 = *m;

    input one;
    init_num(&one);
    insertInEnd(&one, 1);

    int sign = 0;
    /*if both numbers have unequal sign*/
    if(a1.sign != b1.sign) 
	    sign = 1;

    input ex, mp, pr, a = a1, b = b1, b2, quotient, tmpfree;
    init_num(&ex);
    init_num(&mp);
    init_num(&pr);
    init_num(&quotient);

    /*zero division error.*/
    if(b1.size == 0){
	printf("Zero division error detected.\n");
	cont = 1;
	return ex;
    }

    int cmp = compare(a1, b1);

    /*if 2nd no is greater than 1st, result = 0*/
    if(cmp == 2)
	    return quotient;
    
    /*if both no are equal, result = 1*/
    else if(cmp == 0) 
    {
	    one.sign = sign;
	    return one;
    }

    /*first take b1 number of digits in ex*/
    int i = 0;
    for (i = 0; i < b1.size && a1.head; i++) 
    {
        insertInEnd(&ex, a1.head->data);
	    a1.head = a1.head->next;
    }

    /*find i such that mult of 2nd no is 
     * just greater than ex
     * i.e. quotiont digit will be (i-1)*/
    for (i = 1; i < 10; i++) 
    {
        b2 = b;
        insertInEnd(&mp, i);
        pr = mult(&b2, &mp);
        if (compare(ex, pr) == 2)
            break;
        destroy(&mp);
	    destroy(&pr);
    }
    int multiplier = i - 1;

    destroy(&mp);
    destroy(&pr);

    insertInEnd(&mp, multiplier);
    pr = mult(&b1, &mp);
    tmpfree = ex;
    ex = sub(&ex, &pr);
    destroy(&tmpfree);

    insertInEnd(&quotient, multiplier);
    rem_lead_zeros(&quotient);

    destroy(&mp);
    destroy(&pr);

    int count = 0;
    while(a1.head != NULL) 
    {
        insertInEnd(&ex, a1.head->data);	//TODO can be updated 
	    rem_lead_zeros(&ex);

        for (i = 1; i < 10; i++) 
        {
            b2 = b;
            insertInEnd(&mp, i);
            pr = mult(&b2, &mp);
            if (compare(ex, pr) == 2)
                break;
            
	    destroy(&mp);
	    destroy(&pr);
        }
	multiplier = i - 1;

	destroy(&mp);
	destroy(&pr);
    insertInEnd(&mp, multiplier);
    
    pr = mult(&b1, &mp);
    tmpfree = ex;
    ex = sub(&ex, &pr);
    
    destroy(&tmpfree);
    insertInEnd(&quotient, multiplier);
	destroy(&mp);
	destroy(&pr);

        a1.head = a1.head->next;
    }
	
    if(a.sign != b.sign) 
    {
    	quotient.sign = 1;
    }

    destroy(&ex);
    rem_lead_zeros(&quotient);
    quotient.sign = sign;
    return quotient;
}


input modulo(input *l, input *m) {
    /*a % b = a - (b * a/b)*/
    input divisn, multipln;
    divisn = division(l, m);
    multipln = mult(m, &divisn);
    return sub(l, &multipln);
}



/*change base from decimal to any*/
input changeBase(input num, int k) {
    int sign= 0;

    if (k == 10)
	    return num;

    input newbase, temp = num, dec, base, mod, tmpfree;
    init_num(&newbase);
    init_num(&dec);
    init_num(&base);
    init_num(&mod);
    init_num(&tmpfree);

    /*if num is 0, return 0*/
    if (temp.size == 0)
	    return newbase;
    /*if num is neg, convert to positive and 
     * change output sign at last*/
    if (temp.sign == 1) {
	    temp.sign = 0;
	    sign= 1;
    }
    /*to store 10 which will be used in furthur 
     * arithematic operations*/
    insertInEnd(&dec, 1);
    insertInEnd(&dec, 0);

    /*if base is 2 digit no*/
    if(k > 9) {
	insertInEnd(&base, k / 10);
	insertInEnd(&base, k % 10);
    }
    /*if base is 1 digit no*/
    else
	insertInFront(&base, k);

    int count = 0;
    while (temp.size != 0) {
	    count++;
        mod = modulo(&temp, &base);
	int comp = compare(mod, dec);
	/*if mod value is greater or equal to 10,
	 * insert 2 digits*/
	if((comp == 0 || comp == 1)&& mod.head)
		insertInFront(&newbase, mod.head->data*10 + mod.head->next->data);
	/*else insert 1 digit*/
	else if(mod.head)
		insertInFront(&newbase, mod.head->data);
	else
		insertInFront(&newbase, 0);

        temp= division(&temp, &base);
	destroy(&tmpfree);
	tmpfree = temp;
	destroy(&mod);
    }
    
    destroy(&base);
    destroy(&dec);
    newbase.sign = sign;
    return newbase;
}


int val(char c)
{
    if (c >= '0' && c <= '9')
        return (int)c - '0';
    else
        return (int)c - 'A' + 10;
}


input toDeci(list *L, int b){
    input res;
    input temp, multp, base, power, tmpfree;
    init_num(&temp);
    init_num(&multp);
    init_num(&base);
    init_num(&power);
    init_num(&res);

    insertInEnd(&power, 1);

    int dig;
    if(b < 9)
    	insertInEnd(&base, b);
    else {
	insertInEnd(&base, b/10);
        insertInEnd(&base, b % 10);
    }
 
    while(! isempty(*L)) {
	dig = val(get_next(L));
	if(0 <= dig && dig <= 9)
		insertInEnd(&temp, dig);
	else {
		insertInEnd(&temp, dig/10);
		insertInEnd(&temp, dig % 10);
	}

	multp = mult(&temp, &power);

	tmpfree = res;
    	res = add(&res, &multp);
	destroy(&tmpfree);
	destroy(&multp);

	tmpfree = power;
        power = mult(&power, &base);
	destroy(&tmpfree);
	destroy(&temp);
    }
    destroy(&base);
    return res;
}


