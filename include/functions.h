#ifndef functions_h
#define functions_h

#include <string>
#include <sstream>
#include <fstream> //ifstream
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h> //dir
#include <fcntl.h> //readlink
#include <unistd.h> //readlink

#include <signal.h>

#include <X11/Xlib.h>
#include <FL/Fl_File_Chooser.H>

std::string get_symlinkpath(std::string symlink)
{
    struct stat statinfo;

    if((lstat(symlink.c_str(), &statinfo)>0))
    {
        return symlink;
    }

    if (
         (!S_ISLNK (statinfo.st_mode) && statinfo.st_nlink > 1) ||
         (S_ISLNK (statinfo.st_mode))
       )
    {
        std::vector<char> buf(400);
        size_t len;

        do
        {
            buf.resize(buf.size() + 100);
            len = ::readlink(symlink.c_str(), &(buf[0]), buf.size());
        }
        while(buf.size() == len);

        if (len > 0)
        {
            buf[len] = '\0';
            return (std::string(&(buf[0])));
        }
    }
    else
    {
        return symlink;
    }

    return symlink;
}

std::string get_directory_from_filename(std::string input)
{
    std::string filename = input;
    unsigned int finder  = filename.rfind("/");

    if(finder < filename.length())
    {
        filename = filename.erase(finder+1,std::string::npos);
    }
    else
    {
        return "";
    }
    /**return empty if there is no directory*/

    return filename;
}

std::string term_out(std::string terminal_Command_You_Want_Output_From)
{
    if(terminal_Command_You_Want_Output_From.compare("") == 0)
    {
        return "";
    }

    /** set a locale so this works well */
    const char* LANG = getenv("LANG");
    std::string LOCALE;

    if(LANG == NULL)
    {
        LANG = getenv("LANGUAGE");

        if(LANG != NULL)
        {
        std::string tmp   = LANG;
        unsigned int find = tmp.find(".UTF-8");

        if(find > tmp.length())
        {
            tmp += ".UTF-8";
        }

        LOCALE = tmp;

        }
    }
    else
    {
        LOCALE = LANG;
    }

    if(LOCALE.compare("") != 0)
    {
        setlocale(LC_ALL, LOCALE.c_str());
    }

    std::string result   = "";
    const int max_buffer = 1024;
    char buffer[max_buffer];

    FILE *command_p = popen(terminal_Command_You_Want_Output_From.c_str(), "r");

    if (command_p)
    {
        while( fgets(buffer, sizeof(buffer), command_p) !=NULL)
        {
            result.append(buffer);
        }

        pclose(command_p);
    }
    else
    {
       return "";
    }

    if (result.compare("") == 0)
    {
        return "";
    }

    int end = result.length();

    if((end-1) == 0)
    {
        return "";
    }

    if((end) == 0)
    {
        return "";
    }

    return result.erase(end-1,1);
}

std::string terminal_output(std::string terminal_Command_You_Want_Output_From)
{
    return term_out(terminal_Command_You_Want_Output_From);
}

std::string char_to_string(char c)
{
    std::string res(c,1);
    return res;
}

bool is_space(const char x){return std::isspace(x);}

void trace(std::string MSG, int n = 0)
{
    std::cout << MSG;
    if(n != 0)
    {
        std::cout << "-->" << n;
    }
    std::cout << std::endl;
}

std::string color_to_string(const double *rgb)
{
    char tmp[8];
    std::snprintf(tmp, sizeof(tmp), "#%02x%02x%02x", int(rgb[0]), int(rgb[1]), int(rgb[2]));
    return tmp;
}

bool save_string_to_file(std::string MSG,std::string filename)
{
   if(MSG.compare("")==0)
    {
        return false;
    }

    if(filename.compare("")==0)
    {
        return false;
    }

    unsigned int last = filename.rfind('/');

    if( (last + 1) == filename.length())
    {
        return false;
    }

    if(last < filename.length())
    {
        std::string dircheck = filename;
                    dircheck = dircheck.erase(last,std::string::npos);
    }
    else
    {
        return false;
    }

    std::ofstream dest;
    dest.open(filename.c_str());

    if(!dest.is_open())
    {
        return false;
    }

    dest << MSG;
    dest.close();
    return true; 
}

bool test_file(std::string fileWithFullPATH)
{
    //if empty it doesn't exist
    if(fileWithFullPATH.compare("")==0)
    {
      return false;
    }

    std::string dir   = fileWithFullPATH;
    unsigned int find = dir.rfind("/");

    //if there is no directory this isn't correct
    if(find > dir.length())
    {
      // try the PWD if we can
      const char* PWD = getenv("PWD");

      if(PWD == NULL)
      {
            return false;
      }

      dir  = PWD;
      dir += "/";
      fileWithFullPATH = dir + fileWithFullPATH;
    }
    else
    {
      // get the directory
      dir = dir.substr(0,find);
    }
    DIR *mydir                  = NULL;
    struct dirent *entryPointer = NULL;
    mydir                       = opendir(dir.c_str());

    if( dir.rfind('/') != (dir.length()-1) )
    {
        dir += "/";
    }

    if(mydir != NULL)
    {
        while ( (entryPointer=readdir(mydir)) != NULL)
        {
            if(entryPointer->d_type == DT_REG)
            {
                std::string fullpath = entryPointer->d_name;

                if(dir.rfind('/') != (dir.length()-1) )
                {
                    dir += "/";
                }

                fullpath = dir + fullpath;

                if(fullpath.compare(fileWithFullPATH)==0)
                {
                    closedir(mydir);
                    return true;
                }
            }
        }
        closedir(mydir);
    }
    return false;
}


std::vector<std::string> dir_vector(std::string DIRECTORY)
{
    std::vector<std::string> myVector;

    if(!fl_filename_isdir(DIRECTORY.c_str()))
    {
       return myVector;
    }

    DIR *mydir                  = opendir(DIRECTORY.c_str());
    struct dirent *entryPointer = NULL;

    if(DIRECTORY.rfind('/') != (DIRECTORY.length()-1) )
    {
        DIRECTORY += "/";
    }

    if(mydir != NULL)
    {
          while ( (entryPointer=readdir(mydir)) != NULL)
          {
              if(
                  (entryPointer->d_type == DT_REG)&&
                  (entryPointer->d_name[0] != '.')
                )
              {
                  std::string fullpath = entryPointer->d_name;
                  //trace(fullpath);
                  myVector.push_back(fullpath);
              }
          }
    }
    std::vector<std::string>::iterator it;
    std::sort (myVector.begin(), myVector.end());
    it = std::unique (myVector.begin(), myVector.end());
    myVector.resize( std::distance(myVector.begin(),it) );
    return myVector;
}

std::string color_from_name(const char* colorName)
{
    Display *dpy = XOpenDisplay(NULL);
    int scr = XDefaultScreen(dpy);
    Colormap map = DefaultColormap(dpy, scr);
    XColor rgb, nearest_rgb;
    XLookupColor(dpy, map, colorName, &rgb, &nearest_rgb);
    int red = (int)rgb.red>>8;
    int green = (int)rgb.green>>8;
    int blue = (int)rgb.blue>>8;
    char tmp[8];
    std::snprintf(tmp, sizeof(tmp), "#%02x%02x%02x", red, green, blue);
    std::string output = tmp;
    return output;
}


unsigned int get_fl_color(std::string color, unsigned int default_value=0)
{
    if(color.compare("")==0){return default_value;}
    std::string::size_type validator = color.find('#');

    if(validator==0)
    {
        std::string c1 = color.substr (1,6);
                    c1 = "0x" + c1 + "00";

        try
        {
            unsigned int flColor = strtoul(c1.c_str(),0,16);
            return flColor;
        }
        catch(const std::invalid_argument e){return default_value;}
        catch(const std::out_of_range e){return default_value;}
    }

    std::string value = color_from_name(color.c_str());
    return get_fl_color(value, default_value);
}
unsigned int convert_color(std::string num, int default_value=0)
{
    unsigned int NUM = default_value;

    if(num.find("#") == 0)
    {
        return get_fl_color(num, default_value);
    }

    try
    {
        NUM = std::stoul(num);
    }
    catch(const std::invalid_argument e)
    {
        return default_value;
    }
    catch(const std::out_of_range e)
    {
        return default_value;
    }
    return NUM;
}

double convert(std::string num)
{
    if(num.compare("")==0)
    {
        return 0.0;
    }

    std::stringstream out;
    out << num;
    double integer;
    out >> integer;
    return integer;
}

std::string convert(int num)
{
    std::string number;
    std::stringstream out;
    out << num;
    number = out.str();
    return number;
}

std::string convert(double num)
{
    std::string number;
    std::stringstream out;
    out << num;
    number = out.str();
    return number;
}

std::vector<std::string> delim_vec(std::string string_to_become_vector,std::string delimiter)
{
    std::vector<std::string> Vector;
    std::string preComma,postComma;
    std::string original = string_to_become_vector;
    unsigned int found   = 0;
    unsigned int finder  = original.length();
               postComma = original;

    for( found = original.find(delimiter);
         found < finder;
         found = original.find(delimiter)
       )
    {
        preComma  = original;
        postComma = original;
        preComma  = preComma.erase(found,std::string::npos);

        if(preComma.compare("")!=0)
        {
            Vector.push_back(preComma);
        }

        postComma = postComma.erase(0,found+1);
        original  = postComma;
        finder    = original.length();
    }

    if(postComma.compare("")!=0)
    {
        Vector.push_back(postComma);
    }

    return Vector;
}

std::string make_vec_delim(std::vector<std::string> vector,std::string delim)
{
    std::vector<std::string>::iterator itr;
    std::string out="";
    if(vector.empty())
    {
     return out;
    }
    for(itr = vector.begin(); itr!= vector.end(); itr++)
    {
         std::string tmp = *itr;
         if(out.compare("")==0)
         {
             out = tmp;
         }
         else
         {
             out = out + delim + tmp;
         } 
    }
    return out;
}

std::vector<std::string> delim_vec(std::string string_to_become_vector,char delimiter)
{
    return delim_vec(string_to_become_vector,char_to_string(delimiter));
}

std::string vector_to_delim_string(std::vector<std::string> v, std::string delim=",")
{
    std::vector<std::string>::iterator itr;
    std::string res = "";
    if(v.empty())
    {
        return res;
    }

    for( itr = v.begin(); itr!= v.end(); ++itr )
    {

        if(res.compare("")==0)
        {
            res = *itr;
        }
        else
        {
            res = res + delim + *itr;
        }
    }
    return res;
}

std::vector<std::string> join_string_vectors(std::vector<std::string> vectorA,std::vector<std::string> vectorB)
{
    std::vector<std::string> bothVectors;
    bothVectors.reserve(vectorA.size()+vectorB.size());
    bothVectors.insert(bothVectors.end(),vectorA.begin(),vectorA.end());
    bothVectors.insert(bothVectors.end(),vectorB.begin(),vectorB.end());
    return bothVectors;
}

std::vector<std::string> file_to_vector(std::string filename)
{
    std::vector<std::string> fullString;

    if(filename.compare("")==0)
    {
        return fullString;
    }

    if(!test_file(filename))
    {
        trace("No file sent in: "+filename);
    }

    std::string thisLine;
    std::ifstream inputFileStream(filename.c_str(), std::ifstream::in);

    if(inputFileStream.is_open())
    {
      while (getline(inputFileStream,thisLine))
      {
            fullString.push_back(thisLine);
      }
    }

    return fullString;
}

bool test_dir(std::string dirToTest)
{
   if(dirToTest.compare("")==0)
   {
       return false;
   }

   DIR *dir = NULL;
   dir      = opendir(dirToTest.c_str());

   if (dir != NULL)
   {
       closedir(dir);
       return true;
   }

   return false; 
}

int mkdir_p(std::string dirToMake)
{
    if(test_dir(dirToMake.c_str()))
    {
        return 0;
    }

    std::string temporaryDir = dirToMake;
    unsigned int last        = dirToMake.rfind('/');

    if( (last + 1) != dirToMake.length() )
    {
        dirToMake += "/";
    }

    unsigned int found=dirToMake.find_first_of('/');

    while(found < dirToMake.length())
    {
        found++;

        temporaryDir        = dirToMake;
        std::string testing = temporaryDir.erase(found,std::string::npos);
        found               = dirToMake.find_first_of('/',found);

        if(!test_dir(testing.c_str()))
        {
            if(mkdir(testing.c_str(), 0700) > 0)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
    return 0;
}

bool test_exec(std::string execToTest)
{
    if(execToTest.compare("") == 0)
    {
        return false;
    }

/** the list of directories it might check*/
/** /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games*/
    std::string stringEXEC;
    std:: string testPATH, testExec;
    bool result = false;
    const char* path =getenv("PATH");
    std::vector<std::string> paths = delim_vec(path,":");
    std::vector<std::string>::iterator it;

    for (it = paths.begin(); it != paths.end(); it++)
    {
        stringEXEC = execToTest;
        testPATH   = *it;
        stringEXEC = testPATH + "/" + stringEXEC;

        if(test_file(stringEXEC.c_str()))
        {
            return true;
        }
    }

    return result;
}
std::string get_shell_for_C()
{
    std::string shell = term_out("which bash");

    if(!test_exec(shell))
    {
        shell = term_out("which sh");
        if(!test_exec(shell))
        {
            return "";
        }
        else
        {
            shell = shell + " -c '";
        }
    }
    else
    {
        shell = shell + " -c '";
    }

    return shell;
}

int run(std::string program)
{
    std::string shell = get_shell_for_C();

    if(shell.compare("") != 0)
    {
        shell += program;
        shell += "'";
    }
    else
    {
        shell = program;
    }

    trace("run_program::"+shell);
    return system(shell.c_str());
}

std::string file_to_string(std::string filename)
{
    if(filename.compare("")==0){return "";}
    /** make sure it is actually a file */
    if(!test_file(filename))
    {
        return "";
        trace("No file sent in: "+filename);
    }
    std::string thisLine;
    std::string fullString;
    std::ifstream inputFileStream(filename.c_str(), std::ifstream::in);
    if(inputFileStream.is_open())
    {
        while (getline(inputFileStream,thisLine))
        {
            if(fullString.compare("")==0){fullString=thisLine;}
            else{fullString=fullString+"\n"+thisLine;}
        }
    }
    return fullString;
}
#endif