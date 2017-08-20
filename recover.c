/**
 * Recovers jpegs that were deleted off of a memory card
 * 
 * Ellen Cumba
 * CS50
 * Tech901 Code 1.0
 */
 
 #include <stdio.h>
 #include <stdlib.h>
 
 
 //main function accepting one command line argument
 int main (int argc, char *argv[])
 {
    if (argc !=2)
    {
        fprintf(stderr, "Usage: name of a forensic image from which to recover JPEGs\n");//standard error to print if user does not provide one command line argument
        return 1;//error code
    }

    //define argv[1] as infile
    char *infile = argv[1];//file to recover images
 
    FILE *inptr = fopen(infile, "r");//open the memory card file as read only
    
    if (inptr == NULL)//if file is null
    {
        fprintf(stderr, "Could not open %s.\n", infile);//standard error to print if user did not give proper information
        return 2;//error code
    }
    
    //define buffer placeholder
    unsigned char* buffer=malloc(512);  
   //unsigned char buffer[513];     
    
    //filename count
    int filename=0;
    
    FILE*img;
    
    int open=0;
    
    while (!feof (inptr))
    {
        (fread(buffer,512,1,inptr));//**if not eof in while

        //read into the open memory card until you find the beginning of a new jpeg
        if  (buffer [0] == 0xff &&
            buffer [1]==0xd8 &&
            buffer [2]==0xff &&
            (buffer [3] & 0xf0)==0xe0)

        {
                //open and name a new file to write the image
                char outfile[8];
                sprintf(outfile,"%03i.jpg",filename);//outfile 
                
            if (open == 1) //this means file is open but we are at the beginning of image, so close it and open new one, leave open as 1
            {
                    fclose(img);
                    
            }
            else //file is closed so open it, set open to 1
            {
                open=1;
                //open the file, because open = 0 means its closed
            }
        
                img=fopen(outfile,"w");//outfile

                filename++;//increase counter of found jpegs
        }        
            fwrite(buffer,512,1, img);
    }

    //close open files
    fclose(inptr);
    
    //free memory from malloc use        
   free(buffer);

return 0;
}

//create structure for the files
//file is a structure file is the type of variable
//creating the file structure does not need to havw NULL start
//set curser etc... is to set the information. 
//Define it once


