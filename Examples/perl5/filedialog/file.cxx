
#include <windows.h>    // includes basic windows functionality
#include <commdlg.h>    // includes common dialog functionality
#include <dlgs.h>       // includes common dialog template defines
#include <cderr.h>      // includes the common dialog error codes

char* FileSelDlg(const char* pszTitle,
                 const char* pszInitFilename,
                 const char* pszInitDir,
                 const char* pszFilter,
                 unsigned int unFlags)
{
   static char    szFile[MAX_PATH] = "\0";
   static char    szFilter[MAX_PATH] = "\0";
   OPENFILENAME   OpenFileName;

   // Take a copy of the filter and turn any |'s into nulls
   strcpy(szFilter, pszFilter);
   for(char* i = szFilter; *i != '\0'; i++)
   {
      if(*i == '|') *i = '\0';
   }

   // Copy the passed in initial filename into output buffer
   strcpy(szFile, pszInitFilename);

   // Build up the file dialog structure information
   OpenFileName.lStructSize       = sizeof(OPENFILENAME);
   OpenFileName.hwndOwner         = NULL;
   OpenFileName.hInstance         = GetModuleHandle(NULL);
   OpenFileName.lpstrFilter       = szFilter;
   OpenFileName.lpstrCustomFilter = NULL;
   OpenFileName.nMaxCustFilter    = 0;
   OpenFileName.nFilterIndex      = 1;
   OpenFileName.lpstrFile         = szFile;
   OpenFileName.nMaxFile          = sizeof(szFile);
   OpenFileName.lpstrFileTitle    = NULL;
   OpenFileName.nMaxFileTitle     = 0;
   OpenFileName.lpstrInitialDir   = pszInitDir;
   OpenFileName.lpstrTitle        = pszTitle;
   OpenFileName.nFileOffset       = 0;
   OpenFileName.nFileExtension    = 0;
   OpenFileName.lpstrDefExt       = NULL;
   OpenFileName.Flags             = unFlags;

   // Display the dialog, if the user cancel's then make sure
   // the return value is empty
   if(!GetOpenFileName(&OpenFileName))
   {
      strcpy(szFile, "");
   }

   // Return selected filename or empty string if nothing selected
   return szFile;
}

