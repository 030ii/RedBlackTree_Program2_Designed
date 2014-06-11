#ifndef __MEMBER_H__
#define __MEMBER_H__

<<<<<<< HEAD
#define WIDTH "式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式\n"


void alignCenter(char txt[]);
void roadData(FILE *fp, Tree *RBT, Tree *RBTForName);
void textColor(char txt[], int color);
void printBox(char txt[]);

void menu1_member_view(Tree *tree);
void menu2_member_add(Tree *tree, Tree *treeForName);
void menu3_member_modify(Tree *tree, Tree *treeForName);
void menu4_member_delete(Tree *tree, Tree *treeForName); 
void menu6_data_save(Tree *tree);

int isValidName(char txt[]);
int isValidAddr(char txt[]);
int isValidPhone(char txt[]);

=======
#define WIDTH "式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式\n"

void alignCenter(char txt[]);
void roadData(FILE *fp, Tree *RBT, Tree *RBT2);
void menu1_member_view(Tree *tree);
void menu2_member_add(Tree *tree, Tree *tree2);
void menu3_member_modify(Tree *tree, Tree *tree2);
void menu4_member_delete(Tree *tree, Tree *tree2);
void menu6_data_save(Tree *tree);

>>>>>>> 437d1ceccbc6160c54bf5041e32098d6803fea1f
#endif