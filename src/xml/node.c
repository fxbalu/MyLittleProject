/**
 * \file node.c
 * \brief Node related functions
 *
 * Definitions of functions to access a Node's members.
 *
 * \author François-Xavier Balu \<fx.balu@gmail.com\>
 * \date 11 mars 2014
 */


#include "node.h"


/**
 * \brief Create a Node.
 * Create a Node with a name and a value.
 *
 * \param[in] name   Given name for \p n.
 * \param[in] value  Given value for \p n.
 * \param     n      Created Node.
 * \return           Created Node.
 */
Node* createNode(const char* name, const char* value, Node* n)
{
   n = allocateNode(n);
   resetNode(n);
   setNodeName(name, n);
   setNodeValue(value, n);

   return n;
}


/**
 * \brief Allocate memory for a Node.
 *
 * \param n  Memoryless Node
 * \return   Memorized  Node
 */
Node* allocateNode(Node* n)
{
   if((n = malloc(sizeof(Node))) == NULL)
   {
      printf("\nerror in createNode(Node * n)");
   }

   return n;
}


/**
 * \brief Reset a node.
 * Set a Node's members to NULL for the pointers and 0 for the children count.
 *
 * \param n  Reseted Node
 */
void resetNode(Node* n)
{
   if(n != NULL)
   {
      n->name = NULL;
      n->value = NULL;
      n->attr = NULL;
      /* Node's parent */
      n->parent = NULL;
      /* Node's siblings */
      n->previous = n->next = NULL;
      /* Node's children */
      n->first = n->current = n->last = NULL;
      n->cc = 0;
   }
}


/**
 * \brief Set a name for a Node.
 *
 * \param[in] name given name
 * \param     n    modified Node
 */
void setNodeName(const char* name, Node* n)
{
   if(name != NULL && n != NULL)
   {
      if((n->name = malloc((strlen(name) + 1) * sizeof(char))) == NULL)
      {
         printf("error in setNodeName()");
      }
      else
      {
         strcpy(n->name, name);
      }
   }
}


/**
 * \brief Set a value for a Node.
 *
 * \param[in] value given value
 * \param     n     modified Node
 */
void setNodeValue(const char* value, Node* n)
{
   if(value != NULL && n != NULL)
   {
      if((n->value = malloc((strlen(value) + 1) * sizeof(char))) == NULL)
      {
         printf("error in setNodeValue()");
      }
      else
      {
         strcpy(n->value, value);
      }
   }
}


/**
 * \brief Print a Node's data in the terminal.
 *
 * \param[in] n     Read Node.
 * \param[in] mode  Quantity of informations displayed.
 *                  1 = few informations (name and value)
 *                  2 = more informations (name, value and names of parent,
 *                      siblings and children)
 *                  3 = lot of informations (WIP)
 * \todo Implement mode 2 and 3.
 */
void printNode(const Node* n, const int mode)
{
   if(n == NULL)
   {
      printf("Node doesn't exist (NULL pointer).\n");
   }
   else
   {
      /* Name */
      if(n->name == NULL)
      {
         printf("Name = NULL\n");
      }
      else
      {
         printf("Name = \"%s\"\n", n->name);
      }
      /* Value */
      if(n->value == NULL)
      {
         printf("Value = NULL\n");
      }
      else
      {
         printf("Value = \"%s\"\n", n->value);
      }
   }
}
