#include <dir.h>// pour MAXPATH
#include <stdio.h>// pour FILE , fopen,...
#include <math.h>// pour ceil
#define min(a, b)  (((a) < (b)) ? (a) : (b))


bool Is_Good_Char(char chr)
{
        // (chr>=48 && chr<=57) : 0-9
        // (chr>=65 && chr<=90) : A-Z
        // (chr>=97 && chr<=122): a-z
        // 40:( , 41 :) , 45 : - , 95 : _ , 39 : ' , 61 : =
        if( (chr>=48 && chr<=57) || (chr>=65 && chr<=90) || (chr>=97 && chr<=122)
        || (chr==40) || (chr==41) || (chr==45) || (chr==95) || (chr==39))
        {
                return true; 
        }
        else
        {
                return false;
        }
}

int Magic_Processing(char File_Name[MAXPATH])
{
        FILE *Src_File_Pointer;//pointeur vers le fichier source (à décomposer)
        FILE *Magic_File_Pointer;// pointeur vers les fichiers magiques
        long File_Size; // la taille de fichier
        int Nbr_Octet_To_Read_Write;// le nombre des octets à lire/écrir
        int Nbr_Magic_Files;// le nombre des fichiers magiques
        const Magic_File_Name_Length = 180 -  8;// (à  revoire)la longueur des noms des fichiers magiques
                                                // - 8 : pour l'extension (pour ordonner les fichier )
                                                // exemple : .0 ,.1 .... 0.9999999 (max)
        char Current_Dir[MAXDIR];// le repertoire courant
        char Magic_Dir[MAXDIR];// le repertoire magique
        char Magic_File_Name[Magic_File_Name_Length];// les noms des fichiers magiques

        const Buffer_Length = 1024 * 16;
        char Buffer[Buffer_Length];// le buffer de lecture/écriture

        // obtenir le repertoire courant.
        getcwd(Current_Dir,MAXDIR);// mettre le chemin du repertoire courant dans la variable Current_Dir
        //fin : obtenir le repertoire courant.

        // ouverture de fichier source en mode binaire et en lecture seule
        if((Src_File_Pointer=fopen(File_Name,"rb"))==NULL)// si l'opération échoué
        {
                return 1;//impossible d'ouvrir le fichier sources
        }
        //fin : ouverture de fichier source en mode binaire et en lecture seule

        //Calcule de la taille de fichier source.
        fseek (Src_File_Pointer, 0 , SEEK_END);//mettre le pointeur vers la fin du fichier
        File_Size = ftell (Src_File_Pointer);// lire la position courante(dans ce cas 'la fin du fichier')
        rewind (Src_File_Pointer);// remettre le pointeur vers l'emplacement précédent
        //fin : Obtenir la taille de fichier source.

        //création de répertoire magique
        strcpy(Magic_Dir,File_Name);
        strcat(Magic_Dir,"_Magic");
        mkdir(Magic_Dir); // créer le repertoire
        //fin : création d'un répertoire comporte les partitions

        chdir(Magic_Dir); // changer le repertoire courant

        int Remain_Octet = File_Size;// premeirement le nombre d'octet reste = la taille de prtition

        Nbr_Magic_Files = 0;

        while(Remain_Octet>0)//while(!feof(Src_File_Pointer))//tant que le copie pas terminé
        {
                strcpy(Buffer,"");// vider le buffer

                Nbr_Octet_To_Read_Write = min(Buffer_Length,Remain_Octet);

                long Current_Position=ftell(Src_File_Pointer);// obtenir la position courant dans le fichier source
                long Remain_Octet_In_Src_File=File_Size-Current_Position;

                if(Remain_Octet_In_Src_File < Nbr_Octet_To_Read_Write)// si le nombre d'octet reste dans le fichier source < la taille du parttion
                {                                  // ce probleme arriver dans la derniere partition ou si la taille de partition choisi est > la taille de fichier
                        Nbr_Octet_To_Read_Write=Remain_Octet_In_Src_File;
                }

                if(fread(Buffer,Nbr_Octet_To_Read_Write,1,Src_File_Pointer)>0)// si la lecture réussi
                {
                         //--- création des fichiers
                         strcpy(Magic_File_Name,"");
                         for(int i=0;i<Nbr_Octet_To_Read_Write;i++)
                         {
                                if(Is_Good_Char(Buffer[i]))
                                {
                                        strcat(Magic_File_Name,AnsiString(Buffer[i]).c_str());
                                        if(strlen(Magic_File_Name)>=Magic_File_Name_Length || i>=Nbr_Octet_To_Read_Write - 1)
                                        {
                                                strcat(Magic_File_Name,("." + AnsiString(Nbr_Magic_Files)).c_str());// ajout de l'extension
                                                if((Magic_File_Pointer=fopen(Magic_File_Name,"w+b"))!=NULL)
                                                {
                                                        Nbr_Magic_Files ++ ;
                                                        strcpy(Magic_File_Name,"");
                                                        fclose(Magic_File_Pointer);
                                                }
                                                else
                                                {
                                                        return 2;//impossible de créer un fichier magique
                                                }
                                        }
                                }
                                else
                                {
                                        //--
                                        char temp[10]="";
                                        char Code = Buffer[i];

                                        itoa(Code,temp,10);
                                        strcat(Magic_File_Name,"$");
                                        strcat(Magic_File_Name,temp);
                                        strcat(Magic_File_Name,"%");
                                        //--
                                        if(strlen(Magic_File_Name)>=Magic_File_Name_Length - 10/*le code des caractère non Goode (exemple : $-125%)*/
                                         || i==Nbr_Octet_To_Read_Write - 1)
                                        {
                                                strcat(Magic_File_Name,("." + AnsiString(Nbr_Magic_Files)).c_str());// ajout de l'extension
                                                if((Magic_File_Pointer=fopen(Magic_File_Name,"w+b"))!=NULL)
                                                {
                                                        Nbr_Magic_Files ++ ;
                                                        strcpy(Magic_File_Name,"");
                                                        fclose(Magic_File_Pointer);
                                                }
                                                else
                                                {
                                                        return 2;//impossible de créer un fichier magique
                                                }
                                        }
                                }

                         }
                         Remain_Octet -= Nbr_Octet_To_Read_Write;
                }

        }
        fclose(Src_File_Pointer);

}

int Build(AnsiString Dir)
{
        TSearchRec sr;
        AnsiString Magic_File_Name;
        const Buffer_Size = 1024 * 16;
        char Buffer[Buffer_Size]="";
        int Buffer_Length=0;
        FILE * File_Pointer;

        int Extension=0;

        while(FindFirst(Dir + "\\*."+AnsiString(Extension), faAnyFile , sr) == 0)
        {
                for(int i=1;i<=sr.Name.Length();i++)
                {

                        if(sr.Name[i]=='.')
                        {
                                break;
                        }
                        else if(sr.Name[i]=='$')
                        {
                                AnsiString  temp="";
                                int Index2 = 1;
                                int j=1;
                                for(j=1;/*j<=5*/sr.Name[i+j]!='%';j++)
                                {
                                        temp.Insert(sr.Name[i+j],Index2);
                                        Index2++;
                                }
                                char temp2;
                                temp2 = atoi(temp.c_str());
                                /*if(temp2 == 0)
                                {
                                        //temp2 = ;
                                }*/
                                strcat(Buffer,AnsiString(temp2).c_str());
                                Buffer_Length ++;
                                i  = i+j;

                        }
                        else
                        {
                                strcat(Buffer,AnsiString(sr.Name[i]).c_str());
                                Buffer_Length ++;
                        }
                }
                Extension++;
                FindClose(sr);
        }


        // GetParentDir
        AnsiString Parent_Dir;
        int ind=0;

        for(int k =Dir.Length();Dir[k] !='\\';k--)
        {
                ind++;
        }
        Parent_Dir = Dir.SubString(0,Dir.Length() - ind);
        //



        if((File_Pointer=fopen((Parent_Dir + "Magic_file").c_str(),"w+b"))==NULL)
        {
                return 1;
        }
        fwrite(Buffer,Buffer_Length,1,File_Pointer);
        fclose(File_Pointer);

}
