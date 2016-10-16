
/*
The project is developed as part of Computer Architecture class
Project Name: Functional/Pipeline Simulator for simpleRISC Processor
Developer's Name:Nikhil>N ,Allu Krishna Sai Teja
Developer's Email id:2015csb1020@iitrpr.ac.in,2015csb1009@iitrpr.ac.in
Date:16/10/2016
*/

/* mySimpleSim.cpp
   Purpose of this file: implementation file for mySimpleSim
*/


#include "mySimpleSim.h"
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
using namespace std;



//Register file
static unsigned int R[16];
static int PC=-4;
//flags
static int gt,eq;
//memory
static  char MEM[4000];
static int immediate;
//intermediate datapath and control path signals
static unsigned int instruction_word;
static unsigned int operand1;
static unsigned int operand2;
static int branchPC;
static bool isBranchTaken;
static bool isImm;
static bool isAdd;
static bool isSub;
static bool isMul;
static bool isDiv;
static bool isMod;
static bool isLsl;
static bool isLsr;
static bool isCmp;
static bool isAsr;
static bool isOr;
static bool isAnd;
static bool isNot;
static bool isMov;
static bool isSt;
static bool isLd;
static bool isBeq;
static bool isBgt;
static bool isRet;
static bool isWb;
static bool isUBranch;
static bool isCall;
static int imm;
static int aluResult;
static int branchTarget;
static int LdResult;
//static int imm;






int ui=0;








void run_simplesim() {
int io=0;
  while(1) {
    fetch();
    if(instruction_word==0)
	break;
    control();
    decode();
    execute();
    mem();
    write_back();

  }

}

// it is used to set the reset values
//reset all registers and memory content to 0
void reset_proc() {
int k;
for( k=0;k<16;k++){
R[k]=0;
}	
R[14]=3000;
for( k=0;k<4000;k++){
MEM[k]='\0';
}	
	

}

//load_program_memory reads the input memory, and pupulates the instruction
// memory
void load_program_memory(char *file_name)
 {
  FILE *fp;
  unsigned int address, instruction;
  fp = fopen(file_name, "r");
  if(fp == NULL) {
    printf("Error opening input mem file\n");
    exit(1);
  }
  while( fscanf(fp, "%x %x", &address, &instruction) != EOF) {
ui++;
    write_word(MEM, address, instruction);
  }
  fclose(fp);
}

//writes the data memory in "data_out.mem" file
void write_data_memory() {
  FILE *fp;
  unsigned int i;
  fp = fopen("data_out.mem", "w");
  if(fp == NULL) {
    printf("Error opening dataout.mem file for writing\n");
    return;
  }

  for(i=0; i < 4000; i = i+4){
    fprintf(fp, "%x %x\n", i, read_word(MEM, i));
  }
  fclose(fp);
}

//reads from the instruction memory and updates the instruction register
void fetch()
{
          if(isBranchTaken){
             PC=branchPC;
                 }
           else{
		PC=PC+4;
               } 

          
	unsigned int a=read_word(MEM,PC);
	instruction_word=a;
	
	
}
void control()
{
	if(instruction_word>>27==15)
	{
	  isSt=true;
	}
	else
	{
	  isSt=false;
	}
	if(instruction_word>>27==14)
	{
	  isLd=true;
	}
	else
	{
	  isLd=false;
	}
	if(instruction_word>>27==16)
	{
	  isBeq=true;
	}
	else
	{
	  isBeq=false;
	}
	if(instruction_word>>27==17)
	{
	  isBgt=true;
	}
	else
	{
	  isBgt=false;
	}
	if(instruction_word>>27==20)
	{
	  isRet=true;
	}
	else
	{
	  isRet=false;
	}
	if((instruction_word & 0x04000000)>>26 ==1)
	{
	  isImm=true;
	}
	else
	{
	  isImm=false;
	}
	
	if(instruction_word>>27==18)
	{
	  isUBranch=true;
	}
	else
	{
	  isUBranch=false;
	}
	if(instruction_word>>27==19)
	{
	  isCall=true;
	}
	else
	{
	  isCall=false;
	}
	if(instruction_word>>27==0)
	{
	  isAdd=true;
	}
	else
	{
	  isAdd=false;
	}
	if(instruction_word>>27==1)
	{
	  isSub=true;
	}
	else
	{
	  isSub=false;
	}
	if(instruction_word>>27==2)
	{
	  isMul=true;
	}
	else
	{
	  isMul=false;
	}
	if(instruction_word>>27==3)
	{
	  isDiv=true;
	}
	else
	{
	  isDiv=false;
	}
	if(instruction_word>>27==4)
	{
	  isMod=true;
	}
	else
	{
	  isMod=false;
	}
	if(instruction_word>>27==5)
	{
	  isCmp=true;
	}
	else
	{
	  isCmp=false;
	}
	if(instruction_word>>27==10)
	{
	  isLsl=true;
	}
	else
	{
	  isLsl=false;
	}
	if(instruction_word>>27==11)
	{
	  isLsr=true;
	}
	else
	{
	  isLsr=false;
	}
	if(instruction_word>>27==12)
	{
	  isAsr=true;
	}
	else
	{
	  isAsr=false;
	}
	if(instruction_word>>27==7)
	{
	  isOr=true;
	}
	else
	{
	  isOr=false;
	}
	if(instruction_word>>27==6)
	{
	  isAnd=true;
	}
	else
	{
	  isAnd=false;
	}
	if(instruction_word>>27==8)
	{
	  isNot=true;
	}
	else
	{
	  isNot=false;
	}
	if(instruction_word>>27==9)
	{
	  isMov=true;
	}
	else
	{
	  isMov=false;
	}
	
	if(isAdd||isSub||isMul||isDiv||isMod||isLd||isLsl||isLsr||isAsr||isCall||isMov||isAnd||isOr||isNot) 
	{
	  isWb=true;

	}
	else
	{
	  isWb=false;
	}
	
	
	
}
void decode() 
{int e;
if(isRet)
{
operand1=R[15];
cout<<"RETURN INS"<<endl;
}
else{

e=((instruction_word & 0x003c0000)>>18);

operand1=R[e];
}
if(isSt){
cout<<"STORE_INS"<<endl;
e=((instruction_word & 0x03c00000)>>22);
operand2=R[e];
}
else{

e=((instruction_word & 0x0003c000)>>14);

operand2=R[e];
}
 if(isImm){
 if(((instruction_word & 0x00030000)>>16)==0){
if(((instruction_word& 0x00008000)>>15)==1){
imm=(instruction_word | 0xffff0000);
}
else{
imm=(instruction_word & 0x0000ffff);
}
 
	 
 }
 if(((instruction_word & 0x00030000)>>16)==1){
 imm=(instruction_word | 0x0000ffff);
	 
 
 }
 if(((instruction_word & 0x00030000)>>16)==2){
 imm=(instruction_word)<<16;
	 
 
 }
 
 }
 if(isUBranch||isBgt||isBeq||isCall){
cout<<"BRANCH INS "<<endl;
 branchTarget=((instruction_word)& 0x07ffffff)<<2 ;
if(( branchTarget & 0x10000000)>0){
     branchTarget=((branchTarget)|0xe0000000);
}	 
 if(( branchTarget & 0x10000000)>0){
     branchTarget=((branchTarget)|0x00000000);
 }
branchTarget=PC+branchTarget;	 
 }
 
 
 
}
//executes the ALU operation based on ALUop

 
 
 
//perform the memory operation

void execute() 
{
	
	/*1 st Part*/
	if(isRet)
	branchPC=operand1;
	else
        branchPC=branchTarget;

        /*2 nd Part*/
	if(isUBranch||(isBeq&&eq)||(isBgt&&gt)||isCall||isRet)
	{
	isBranchTaken=true;
	}
	else 
	isBranchTaken=false;
	/*ALU PART */
	int A,B;	
	if(isImm){
	B=imm;}
	else{
	B=operand2;}
	A=operand1;
	if(isMul)
	{
	cout<<"MULTIPLICATION "<<endl;
      
	aluResult=A*B;
	}
	else if(isDiv)
	{
	cout<<"DIV "<<endl;
	aluResult=A/B;
	
	}
	else if(isMod)
	{
	cout<<"MOD "<<endl;
	aluResult=A%B;
	}
	else if(isOr)
	{
	cout<<"Or "<<endl;
	aluResult=A|B;
	}
	
	else if(isNot)
	{
	aluResult=~B; 
	cout<<"NOT "<<endl;
	}
	
	else if(isMov) 
	{
	
	aluResult=B;
	cout<<"MOV "<<endl;
	//cout<<operand2<<endl;
	}
	
	else if(isAnd)
	{
	aluResult=A&B;
	cout<<"AND "<<endl;
	}

	else if(isAdd)
	{
	cout<<"ADD "<<endl;
	aluResult=A+B;
	}

	else if(isSub)
	{
	cout<<"SUB "<<endl;
	aluResult=A-B;
	}

	else if(isCmp)
	{
	cout<<"CMP INS "<<endl;
	if(A>B)
	{
	   eq=false;
	   gt=true;	
	}
	else if(A==B)
	{
	   eq=true;
	   gt=false;
	}
	}
	
	else if(isLd)  
	{
	cout<<"LOAD "<<endl;
	aluResult=A+B;
	}
	
	else if(isSt)
	{
	cout<<"STORE "<<endl;
	aluResult=A+B;
	cout<<"A IS "<<R[13]<<endl;
	}
	
	else if(isLsl)
	{
	cout<<"LSL "<<endl;
	aluResult=A<<B;
	}
	
	else if(isLsr)
	{
	cout<<"LSR "<<endl;
	aluResult=A>>B;
	}
	
	else if(isAsr)
	{
	unsigned int a=A|0x80000000;
	unsigned int b=A<<1;
	b=b>>B;
	b=b|a;
	aluResult=b;
	cout<<"ASR "<<endl;
	}
		cout<<"ALU RESULT IS "<<aluResult<<endl;   
	
}

void mem() {
	if(isSt){
write_word(MEM,aluResult,operand2);
cout<<operand2<<"   "<<aluResult<<endl;
 }	
if(isLd){
LdResult=read_word(MEM,aluResult);
}	
	
	
	
}
//writes the results back to register file
void write_back() 
{
	int result;
	int y;
	if(isLd)
	{
	result=LdResult;
	}
	else if(isCall){
	result=PC+4;
	}
	else
	{
	result=aluResult;
	}
	if(isWb)
	{
	if(isCall)
	{
	  R[15]=result;
  	}
	else
	{
	y=((instruction_word & 0x03c00000)>>22);
	R[y]=result;
  	cout<<"Dest "<<y<<endl;  
  	}	
	}
}


int  read_word(char *mem, unsigned int address) {
  int *data;
  data =  (int*) (mem + address);
  return *data;
}

void write_word(char *mem, unsigned int address, unsigned int data) {
  int *data_p;
  data_p = (int*) (mem + address);
  *data_p = data;
}
