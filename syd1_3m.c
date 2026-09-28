#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "astdef.h"
#include "y.tab.h"

extern AstNode *TreeRoot;
int yyparse(void);

void kena(int n)
{  int i;
   
   for(i=0; i<n; i++) printf(" ");
}

void traverse(AstNode *p,int n)
{  int i;

   n=n+3;
   if(p)
   {
      switch (p->NodeType)
      {
         case astEmptyProgram: 
            kena(n); printf("astEmptyProgram\n"); 
         break;
         case astProgram: 
            kena(n); printf("astProgram\n"); 
         break;
         case astMethList: 
            kena(n); printf("astMethList\n"); 
         break;
         case astMeth: 
            kena(n); printf("astMeth\n"); 
         break;
         case astParams: 
            kena(n); printf("astParams\n"); 
         break;
         case astFormals: 
            kena(n); printf("astFormals\n"); 
         break;
         case astBody: 
            kena(n); printf("astBody\n"); 
         break;
         case astDecls: 
            kena(n); printf("astDecls\n"); 
         break;   
         case astDec: 
            kena(n); printf("astDec\n"); 
         break;
         case astVars:
            kena(n); printf("astVars\n"); 
         break;
         case astStmts: 
            kena(n); printf("astStmts\n"); 
         break;
         case astStmtReturn: 
            kena(n); printf("astStmtReturn\n"); 
         break;
         case astStmtIf: 
            kena(n); printf("astStmtIf\n"); 
         break;
         case astStmtWhile: 
            kena(n); printf("astStmtWhile\n"); 
         break;
         case astStmtBreak:
            kena(n); printf("astStmtBreak\n"); 
         break;
         case astAssign: 
            kena(n); printf("astAssign\n"); 
         break;
         case astMult:
            kena(n); printf("astMult\n"); 
         break;
         case astDiv: 
            kena(n); printf("astDiv\n"); 
         break;
         case astMod: 
            kena(n); printf("astMod\n"); 
         break;
         case astAdd: 
            kena(n); printf("astAdd\n"); 
         break;
         case astSub: 
            kena(n); printf("astSub\n"); 
         break;
         case astGreater: 
            kena(n); printf("astGreater\n"); 
         break;
         case astGrEq: 
            kena(n); printf("astGrEq\n"); 
         break;
         case astLess: 
            kena(n); printf("astLess\n"); 
         break;
         case astLeEq: 
            kena(n); printf("astLeEq\n"); 
         break;
         case astEq: 
            kena(n); printf("astEq\n"); 
         break;
         case astNotEq: 
            kena(n); printf("astNotEq\n"); 
         break;
         case astExpr: 
            kena(n); printf("astExpr\n"); 
         break;
		 case astAddExpr: 
            kena(n); printf("astAddExpr\n"); 
         break;
         case astMethCall: 
            kena(n); printf("astMethCall\n"); 
         break;
         case astActuals: 
            kena(n); printf("astActuals\n"); 
         break;
         case astArgs: 
            kena(n); printf("astArgs\n"); 
         break;
         case astLoc: 
            kena(n); printf("astLoc\n"); 
         break;
         case astNum: 
            kena(n); printf("astNum\n"); 
         break;
         case astTerm: 
            kena(n); printf("astTerm\n"); 
         break;
         case astDecVal: 
            kena(n); printf("astDecVal\n"); 
         break;
		 case astVarsVal: 
            kena(n); printf("astVarsVal\n"); 
         break;
         case astEmptyParams: 
            kena(n); printf("astEmptyParams\n"); 
         break;
         case astTypeInt: 
            kena(n); printf("astTypeInt\n"); 
         break;
         case astEmptyDecls: 
            kena(n); printf("astEmptyDecls\n"); 
         break;
         case astEmpty: 
            kena(n); printf("astEmpty\n"); 
         break;
         case astMethod: 
            kena(n); printf("astMethod\n"); 
         break;
         case astBlock: 
            kena(n); printf("astBlock\n"); 
         break;
		 case astMethListLast: 
            kena(n); printf("astMethListLast\n"); 
         break;
		 case astTrue: 
            kena(n); printf("astTrue\n"); 
         break;
		 case astFalse: 
            kena(n); printf("astFalse\n"); 
         break;
         default: 
            printf("AGNOSTO=%d\n",p->NodeType);
      }
      for(i=0; i<4; i++) traverse(p->pAstNode[i],n);
   }
}

int hasReturned = 0;
int returnValue = 0;

symbol *ACTS[16];
int nACTS=-1;
void ProcessProgram(AstNode *p, int lev){
	CodeGeneration(p->pAstNode[0],lev+1,f,t);
}
void ProcessMethList(AstNode *p, int lev){
	
	pushM(p->pAstNode[0]);
	pushS(p->pAstNode[0]->SymbolNode);
	CodeGeneration(p->pAstNode[1],lev+1,f,f);
	
}
void ProcessMethListLast(AstNode *p, int lev){
	if(strcmp(p->pAstNode[0]->SymbolNode->name,"main")!=0){
		printf("Err:main not defined\n");
        exit(1);
	}
	CodeGeneration(p->pAstNode[0],lev+1,f,t);
	
}
void ProcessMeth(AstNode *p, int lev){
	
	symbol *scopM = new_symbol("");
	scopM->scopeMarker=1;
	scopM->lvalue=0;
	pushS(scopM);
	
	CodeGeneration(p->pAstNode[0],lev+1,f,t);
	CodeGeneration(p->pAstNode[1],lev+1,f,f);
	
	hasReturned = 0;
    returnValue = 0;
	CodeGeneration(p->pAstNode[2],lev+1,f,f);
	pop_until_block();
}
void ProcessParams(AstNode *p, int lev){
	if(!ACTS[nACTS]){
		printf("Err:Actuals and parameters mismatch (actuals<parameters)");
		exit(1);
	}
	p->SymbolNode->timi = ACTS[nACTS]->timi;

	pushS(p->SymbolNode);
	nACTS--;
	CodeGeneration(p->pAstNode[0],lev+1,f,t);
}
void ProcessEmptyParams(AstNode *p, int lev){
	
	if(nACTS>-1){
		printf("Err:Actuals and parameters mismatch (actuals>parameters)");
		exit(1);
	}
}
void ProcessBody(AstNode *p, int lev){	
	CodeGeneration(p->pAstNode[0],lev+1,f,t);
	CodeGeneration(p->pAstNode[1],lev+1,f,f);
}
void ProcessDecls(AstNode *p,int lev){
	CodeGeneration(p->pAstNode[0], lev+1, f, t);
	CodeGeneration(p->pAstNode[1], lev+1, f, f);
}
void ProcessDec(AstNode *p,int lev){
	pushS(p->SymbolNode);
	CodeGeneration(p->pAstNode[0], lev+1, f, t);
}
void ProcessDecVal(AstNode *p,int lev){
	pushS(p->SymbolNode);
	CodeGeneration(p->pAstNode[0],lev+1,f,t);
	symbol *pt=find_sym(p->SymbolNode->name);
	pt->timi=p->pAstNode[0]->SymbolNode->timi;
	printf("%s = %d\n",pt->name,pt->timi);
	CodeGeneration(p->pAstNode[1],lev+1,f,f);
}
void ProcessStmts(AstNode *p,int lev){
	CodeGeneration(p->pAstNode[0], lev+1, f, t);
	CodeGeneration(p->pAstNode[1], lev+1, f, f);
}
void ProcessReturn(AstNode *p, int lev){
	CodeGeneration(p->pAstNode[0], lev+1, f, t);
	
	returnValue = p->pAstNode[0]->SymbolNode->timi;
    hasReturned = 1;
}

void ProcessIf(AstNode *p,int lev){
	CodeGeneration(p->pAstNode[0],lev+1,f,f);
	if(p->pAstNode[0]->SymbolNode->timi>0){
		CodeGeneration(p->pAstNode[1],lev+1,f,f);
	}
	else{
		CodeGeneration(p->pAstNode[2],lev+1,f,f);
	}
}

void ProcessWhile(AstNode *p,int lev){
    pushW();
    CodeGeneration(p->pAstNode[0], lev+1, f, f);
    while(p->pAstNode[0]->SymbolNode->timi > 0 && !isBreak()) {
        CodeGeneration(p->pAstNode[1], lev+1, f, f);
        if(!isBreak()) {
            CodeGeneration(p->pAstNode[0], lev+1, f, f);
        }
    }
    popW();
}

void ProcessBreak(AstNode *p,int lev){
    checkBreak();
	setBreak();
}
void ProcessAssign(AstNode *p,int lev){
	CodeGeneration(p->pAstNode[1],lev+1,f,f);
	CodeGeneration(p->pAstNode[0],lev+1,f,f);
	
	if(p->pAstNode[0]->SymbolNode->lvalue==0){
		printf("Err:Left symbol does not match an lvalue");
		exit(1);
	}

	p->pAstNode[0]->SymbolNode->timi=p->pAstNode[1]->SymbolNode->timi;
	printf("%s = %d\n",p->pAstNode[0]->SymbolNode->name,p->pAstNode[0]->SymbolNode->timi);
}
void ProcessExpr(AstNode *p,int lev){
	
	CodeGeneration(p->pAstNode[0],lev+1,f,t);
	CodeGeneration(p->pAstNode[2],lev+1,f,f);
	int a = p->pAstNode[0]->SymbolNode->timi;
	int b = p->pAstNode[2]->SymbolNode->timi;
	

	switch(p->pAstNode[1]->NodeType){
		case astLeEq:
			p->SymbolNode->timi= a <= b;
			break;
		case astLess:
			p->SymbolNode->timi= a < b;
			break;
		case astGreater:
			p->SymbolNode->timi= a > b;
			break;
		case astGrEq:
			p->SymbolNode->timi= a >= b;
			break;
		case astEq:
			p->SymbolNode->timi= a == b;
			break;
		case astNotEq:
			p->SymbolNode->timi= a != b;
			break;
	}
	printf("Expression value=%d\n",p->SymbolNode->timi);
}
void ProcessAddExpr(AstNode *p,int lev){
	
	CodeGeneration(p->pAstNode[0],lev+1,f,t);
	CodeGeneration(p->pAstNode[2],lev+1,f,f);
	int a = p->pAstNode[0]->SymbolNode->timi;
	int b = p->pAstNode[2]->SymbolNode->timi;
	switch(p->pAstNode[1]->NodeType){
		case astAdd:
			p->SymbolNode->timi=a+b;
			break;
		case astSub:
			p->SymbolNode->timi=a-b;
			break;
	}
}
void ProcessTerm(AstNode *p,int lev){
	
	CodeGeneration(p->pAstNode[0],lev+1,f,t);
	CodeGeneration(p->pAstNode[2],lev+1,f,f);
	int a = p->pAstNode[0]->SymbolNode->timi;
	int b = p->pAstNode[2]->SymbolNode->timi;
	
	switch(p->pAstNode[1]->NodeType){
		case astMult:
			p->SymbolNode->timi=a*b;
			break;
		case astDiv:
			if(b!=0){
				p->SymbolNode->timi=a/b;
			}
			else{
				printf("Err:Undefined expression");
				exit(1);
			}
			break;
			
	}
}
void ProcessLoc(AstNode *p,int lev){
	p->SymbolNode = checkCall(p->SymbolNode->name);
}
void ProcessMethCall(AstNode *p,int lev){
	nACTS = -1;
	
	symbol *pt = checkCall(p->pAstNode[0]->SymbolNode->name);
	AstNode *CalledMethod = find_Meth(pt->name);
	CodeGeneration(p->pAstNode[1],lev+1,f,f);

    CodeGeneration(CalledMethod,lev,f,f);
	symbol *st = new_symbol("");
	p->SymbolNode = st;
    if (hasReturned) {
        p->SymbolNode->timi = returnValue;
        printf("%s Returned %d\n",p->pAstNode[0]->SymbolNode->name,p->SymbolNode->timi);
    }
}
void ProcessActuals(AstNode *p,int lev){
	CodeGeneration(p->pAstNode[0],lev+1,f,t);
	CodeGeneration(p->pAstNode[1],lev+1,f,f);
	ACTS[++nACTS]=p->pAstNode[1]->SymbolNode;
}

void CodeGeneration(AstNode *p, int lev, int lvalue, int leftChild){
	switch(p->NodeType){
		case astEmptyProgram:
			break;
		case astProgram: 
			ProcessProgram(p,lev);
			break;
		case astMethList:
			ProcessMethList(p,lev);
			break;
		case astMethListLast:
			ProcessMethListLast(p,lev);
			break;
		case astMeth:
			ProcessMeth(p,lev);
			break;
		case astParams:
			ProcessParams(p,lev);
			break;
		case astEmptyParams:
			ProcessEmptyParams(p,lev);
			break;
		case astBody:
			ProcessBody(p,lev);
			break;
		case astDecls:
			ProcessDecls(p,lev);
			break;
		case astEmptyDecls:
			break;
		case astDec:
			ProcessDec(p,lev);
			break;
		case astDecVal:
			ProcessDecVal(p,lev);
			break;
		case astEmpty:
			break;
		case astStmts:
			ProcessStmts(p,lev);
			break;
		case astStmtReturn:
			ProcessReturn(p,lev);
			break;
		case astStmtIf:
			ProcessIf(p,lev);
			break;
		case astStmtWhile:
			ProcessWhile(p,lev);
			break;
		case astStmtBreak:
			ProcessBreak(p,lev);
			break;
		case astAssign:
			ProcessAssign(p,lev);
			break;
		case astExpr:
			ProcessExpr(p,lev);
			break;
		case astAddExpr:
			ProcessAddExpr(p,lev);
			break;
		case astTerm:
			ProcessTerm(p,lev);
			break;
		case astLoc:
			ProcessLoc(p,lev);
			break;
		case astMethCall:
			ProcessMethCall(p,lev);
			break;
		case astActuals:
			ProcessActuals(p,lev);
			break;
	}	
}
	

int main(void)
{
	AstNode *p;
    int err = yyparse();
    
	if(!err){
		p=TreeRoot;
		traverse(p,-3);
		CodeGeneration(p,0,f,f);
		printf("%d\n",returnValue);
		printf("No Errors");
	}
	
	return 0;
}