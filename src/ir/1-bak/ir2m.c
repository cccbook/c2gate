#include "ir2m.h"

void ir2macro(FILE *fp, IR *p) {
  int t=p->t, t1=p->t1, t2=p->t2, label=p->label;
  char *s = p->s, *op = p->op, digit[2];
  if (isDebug) irWrite(stdout, p);
  switch (p->type) {
    // case IrCall: error("IrCall"); break;
    // case IrArg:  error("IrArg"); break;
    case IrAssignSt:
      fprintf(fp, ".set  %s = t%d", s, t); // s=t
      break;
    case IrAssignTs:
      digit[0] = isdigit(*s) ? 'c' : ' ';
      fprintf(fp, ".set%s t%d = %s", digit, t, s); // t=s
      break;
    case IrLabel: // (label)
      fprintf(fp, "(L%d)", label);
      break;
    case IrLabelStr: // (label)
      fprintf(fp, "(%s)", labelStr);
      break;
    case IrGoto: // goto label
      fprintf(fp, ".goto L%d", label);
      break;
    case IrGotoStr: // goto label
      fprintf(fp, ".goto %s", labelStr);
      break;
    case IrIfGoto: // if t goto label
      fprintf(fp, ".if t%d goto L%d", t, label);
      break;
    case IrIfNotGoto: // ifnot t goto label
      fprintf(fp, ".ifnot t%d goto L%d", t, label);
      break;
    case IrOp2: // t = t1 op t2
      fprintf(fp, ".op   t%d = t%d %s t%d", t, t1, op, t2);
      break;
    default: 
      error("ir.type %d not found!", p->type);
  }
  fprintf(fp, "\n");
}

void ir2m(char *mFile) {
  FILE *mF = fopen(mFile, "w");
  for (int i=0; i<irTop; i++) {
    ir2macro(mF, &ir[i]);
  }
  fclose(mF);
}