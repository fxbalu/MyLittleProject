/**
 * \file xml_test.c
 * \brief Test XML file related functions
 *
 * \author François-Xavier Balu \<fx.balu@gmail.com\>
 * \date 14 mars 2014
 */


 #include "xml.h"


 /**
 * \brief Testing program for XML file
 * Main program testing functions from "xml.h".
 *
 * \param argc int
 * \param argv[] char*
 * \param arge char**
 * \return int
 */
int main(int argc, char* argv[], char** arge)
{
   char testXMLFilePath[10] = "test.xml";
   XML_File* testXMLFile;

   testXMLFile = NULL;
   printf("Test program\n============\n");

   printf("Checking \"test.xml\" file...\n");
   createXMLFile(testXMLFilePath, testXMLFile);
   printf("done.\n");

   return 0;
}
