/**
 * \file attribute.c
 * \brief Attribute related functions
 *
 * Definitions of functions to access an Attribute's members and insert and
 * remove it from a Node.
 *
 * \author François-Xavier Balu \<fx.balu@gmail.com\>
 * \date 13 mars 2014
 */


 #include "node.h"


 /**
 * \brief Create an Attribute.
 * Create an Attribute with a name and a value.
 *
 * \param[in] name   Given name for \p a.
 * \param[in] value  Given value for \p a.
 * \param     a      Created Attribute.
 * \return           Created Attribute.
 */
Attribute* createAttribute(const char* name, const char* value, Attribute* a)
{
   a = allocateAttribute(a);
   resetAttribute(a);
   setAttributeName(name, a);
   setAttributeValue(value, a);

   return a;
}


/**
 * \brief Allocate memory for an Attribute.
 *
 * \param a  Memoryless Attribute
 * \return   Memorized  Attribute
 */
Attribute* allocateAttribute(Attribute* a)
{
   if((a = malloc(sizeof(Attribute))) == NULL)
   {
      printf("\nerror in createAttribute(Attribute * a)");
   }

   return a;
}


/**
 * \brief Reset an Attribute.
 * Set an Attribute's members to NULL.
 *
 * \param a  Reseted Attribute
 */
void resetAttribute(Attribute* a)
{
   if(a != NULL)
   {
      a->name = NULL;
      a->value = NULL;
   }
}


/**
 * \brief Set a name for an Attribute.
 *
 * \param[in] name given name
 * \param     a    modified Attribute
 */
void setAttributeName(const char* name, Attribute* a)
{
   if(name != NULL && a != NULL)
   {
      if((a->name = malloc((strlen(name) + 1) * sizeof(char))) == NULL)
      {
         printf("error in setAttributeName()");
      }
      else
      {
         strcpy(a->name, name);
      }
   }
}


/**
 * \brief Set a value for an Attribute.
 *
 * \param[in] value given value
 * \param     a     modified Attribute
 */
void setAttributeValue(const char* value, Attribute* a)
{
   if(value != NULL && a != NULL)
   {
      if((a->value = malloc((strlen(value) + 1) * sizeof(char))) == NULL)
      {
         printf("error in setAttributeValue()");
      }
      else
      {
         strcpy(a->value, value);
      }
   }
}


/**
 * \brief Insert an Attribute in a Node.
 * Insert an Attribute in a Node before the first Attribute already attached to
 * said Node.
 *
 * \param a  Added Attribute.
 * \param n  Modified Node.
 */
void insertFirstAttribute(Attribute* a, Node* n)
{
   if((a != NULL) && (n != NULL))
   {
      a->next = n->attr;
      n->attr = a;
   }
}

/**
 * \brief Insert an Attribute in a Node.
 * Insert an Attribute in a Node after the last Attribute already attached to
 * said Node.
 *
 * \param a  Added Attribute.
 * \param n  Modified Node.
 */
void insertLastAttribute(Attribute* a, Node* n)
{
   Attribute* temp;

   if(n != NULL)
   {
      /* No Attribute attached to Node */
      if(n->attr == NULL)
      {
         n->attr = a;
      }
      /* One Attribute or more */
      else
      {
         temp = n->attr;
         while(temp->next != NULL)
         {
            temp = temp->next;
         }
         temp->next = a;
      }
   }
}


/**
 * \brief Delete the first Attribute of a Node.
 * Deleted Node is not freed from memory.
 *
 * \param n  Modified Node
 * \return   Deleted Attribute
 */
Attribute* deleteFirstAttribute(Node* n)
{
   Attribute* deleted;

   deleted = NULL;
   if(n != NULL)
   {
      deleted = n->attr;
      /* One or more Attribute attached to Node */
      if(deleted != NULL)
      {
         n->attr = deleted->next;
         deleted->next = NULL;
      }

   }

   return deleted;
}


/**
 * \brief Delete the last Attribute of a Node
 *
 * \param n  Modified Node
 * \return   Deleted Attribute
 */
Attribute* deleteLastAttribute(Node* n)
{
   Attribute* temp, * deleted;

   deleted = NULL;
   if(n != NULL)
   {
      /* At least one Attribute attached to Node */
      if(n->attr != NULL)
      {
         temp = n->attr;
         /* Only one Attribute */
         if(temp->next == NULL)
         {
            deleted = temp;
            n->attr = NULL;
         }
         /* Two or more Attribute */
         else
         {
            while(temp->next->next != NULL)
            {
               temp = temp->next;
            }
            deleted = temp->next;
            temp->next = NULL;
         }
      }
   }

   return deleted;
}


/**
 * \brief Tell if a Node has Attribute or not.
 *
 * \param n  Checked Node.
 * \return   \c true if Node n has at least one Attribute, \c false if not.
 */
Boolean hasAttribute(Node* n)
{
   return(n->attr != NULL);
}



/**
 * \brief Destroy every Attributes of a Node
 * Free memory allocated to members (name and value) and Attributes.
 *
 * \param n  Node where Attributes are destroyed.
 */
void destroyEveryAttributes(Node* n)
{
   Attribute* temp;

   if(n != NULL)
   {
      while(hasAttribute(n))
      {
         temp = deleteFirstAttribute(n);
         if(temp->name != NULL)
            free(temp->name);
         if(temp->value != NULL)
            free(temp->value);
         free(temp);
      }
   }

}
