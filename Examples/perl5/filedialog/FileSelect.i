%module FileSelect
%{
%}

// File Selection Dialog
extern char* FileSelDlg(const char* DialogTitle, 
                        const char* InitialFilename,
                        const char* InitialDir,
                        const char* FiletypeFilter,
                        unsigned int DialogFlags);

// File Selection Flags
#define OFN_READONLY                 0x00000001
#define OFN_OVERWRITEPROMPT          0x00000002
#define OFN_HIDEREADONLY             0x00000004		// Hide Read-Only checkbox
#define OFN_NOCHANGEDIR              0x00000008
#define OFN_ALLOWMULTISELECT         0x00000200		// Allow >1 File to be selected
#define OFN_EXTENSIONDIFFERENT       0x00000400
#define OFN_PATHMUSTEXIST            0x00000800
#define OFN_FILEMUSTEXIST            0x00001000
#define OFN_CREATEPROMPT             0x00002000
#define OFN_SHAREAWARE               0x00004000
#define OFN_NOREADONLYRETURN         0x00008000
#define OFN_NOTESTFILECREATE         0x00010000
#define OFN_NONETWORKBUTTON          0x00020000		// Hide Network button
#define OFN_NOLONGNAMES              0x00040000		// Force no long names for Win 4.x
#define OFN_EXPLORER                 0x00080000    // New look dialog, win95/NT4 only
#define OFN_NODEREFERENCELINKS       0x00100000		// Do not automatically dereference .lnks
#define OFN_LONGNAMES                0x00200000    // Force long names for Win 3.x

// Grab some additional Perl code for our File selector
%pragma(perl5) include="select.ipl"












