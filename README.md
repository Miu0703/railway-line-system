# railway-line-system
In this part of the HW we will write a program that will help in design and declaration of railway line system. The program enables to add or delete stations and lines and get information concerning existing stations/lines. The program supports textual interface as explained in the following.
Part A :
1. The file GSet.h supplies an interface to the Generic ADT GSet.
 Write an implementation to GSet in a file called GSet.c.
 Requirements: The implementation MUST be done by using the Generic ADT List
 whose interface is given in the file List.h. Must NOT use any other data types but
 ONLY the given List. No need to implement List. The full implementation of List is
 also given by means of libmtm.a library.
 Remark : if needed then can write more file/files in addition to GSet.c
2. The file GSet_test.c contains an example to UNIT TEST of GSet.
Complete the missing code. Add more UNIT TESTS for ALL the interface operations
that are declared for GSet. Try to have (if possible) a separate function for each
interface operation of GSet. This function will do the UNIT TEST for this interface
operation.
3. Run your unit test program and verify that all tests succeed.
 Notice :
 Compilation/Link is to be done as follows :
 gcc -std=c99 –Wall -Werror -pedantic-errors -DNDEBUG -o GSet_test.exe GSet_test.c
 GSet.c -L. –lmtm
 Verify that the appropriate libmtm.a is located in the current directory.
 If you have more files in addition to GSet.c the, of course, need also to join these files to the
 compilation/link.
 General Guidelines : Pay attention to all what we have learned –
 abstraction, hiding, modularity, memory leak (malloc , free, use valgrind), use assert in
 relevant cases etc.
 Document your code with highlight remarks when is relevant to have a readable code.
 As a whole, we try to have the code written in a manner of self explanatory, so that such
additional remarks may be needed only in main locations in the code.
in Part A you should submit the following files :
GSet.c, GSet_test.c (and more files, if any, that you may write concerning GSet). Do NOT need
to submit GSet.h, not List.h

Part B :
In this part of the HW we will write a program that will help in design and declaration of railway
line system. The program enables to add or delete stations and lines and get information
concerning existing stations/lines. The program supports textual interface as explained in the
following.
We’ll deal with the following entities :
Station
characterized by
1. a name (string no longer than 50 chars (without ‘\0’, regular ASCII characters).
2. ID number (positive with 4 digits greater than 1001. Each station has a unique ID
number.
3. number of platforms (greater or equal to 1).
Line
Characterized by :
1. ID number (5 digits, grater than 10000. Every Line has a unique ID number.
2. List of Station IDs that defines the route of the line – 1 direction.
System
Characterized by :
1. Set of Stations.
2. Set of Lines.
Here are the various operations to be supported by the textual interface :
----------------------------------------------------------------------------------------------------------------------
1. init <system_name>
create an initial basic system. No stations, nor lines yet.
<system_name> is any textual name of the system. No more than 50 chars. No spaces. At least
1 no “white” character.
Output to be displayed :
Done if success. Problem if fail from any reason.
Remark : Can NOT do init if already exists any system. Must do Destroy and then, when no
System any more, can do another init. Doing init when already exists a system will display
Problem. The program supports a unique system in any time. (no more than 1 system at a
single time).
----------------------------------------------------------------------------------------------------------------------
2. destroy
closing and deleting the current system. If no system then nothing is done. The operation
always succeeds. Done is displayed in any case.
----------------------------------------------------------------------------------------------------------------------
3. addStation <station_name> <station_id> <num_of_platforms>
parameters :
<station_name> - name of a station. No more than 50 characters without “white” spaces.
<station_id> - 4 digits greater than 1000.
<num_of_platforms> - grater than 0.
Output to be displayed : Done if succeed. Problem otherwise.
Possible problem cases : no system yet, already exists a station with the same name (case
sensitive) or with the same id, memory problem.
----------------------------------------------------------------------------------------------------------------------
4. deleteStation <station_id>
parameters :
<station_id> ID number of station to be deleted.
Output to be displayed : Done if succeed. Problem in another case.
Possible Problem cases : no system exists, no station with the requested ID, the station appears
in at least 1 of the lines exists in the system. (This means that a station can be deleted ONLY if it
does NOT appear in any line that currently exists in the system).
----------------------------------------------------------------------------------------------------------------------
5. addLine <line_id> <station_id1> <station_id2>
parameters :
<line_id> 5 digits greater than 10000.
<station_id1> the ID number of the source station (in 1 direction out of 2 directions).
<station_id2> the ID number of the destination station (in 1 direction out of 2 directions).
Output to be displayed : Done if succeed. Problem otherwise.
Possible Problem cases :
No system, already exists a line with the same ID number, source/target destination does not
exist, id1==id2 (we do not enable circular line), memory problems.
----------------------------------------------------------------------------------------------------------------------
6. updateLine <line_id> <station_id> <position>
parameters :
<line_id> ID number of a line.
<station_id> ID number of a station
<position> the location of the station in the line according to the line path 1 direction. Can
assume that this is a number equal or greater than 1.
If the station still does not appear in the line route, then it is added to the line in such a way
that its location in the line route 1 direction is <position>. Relative positions of other stations
are updated accordingly. all positions are successive numbers starting from 1 and go up. If
<position> is greater then the number of stations in the line (after adding the new station) then
the station will be added in last position (last station) according to line route 1 direction.
If station already exists in line route, then it is updated to be located in the new position in the
line route 1 direction. All other positions of other stations are updated accordingly. If <position>
is greater then the number of stations in the line then the station will be added in last position
(last station) according to line route 1 direction.
Output to be displayed : Done if succeed. Problem otherwise.
Possible Problem cases : No system, no line with <line_id>, no station with <station_id>,
memory problems.
----------------------------------------------------------------------------------------------------------------------
7. removeLine <line_id>
parameters :
<line_id> ID of line to be deleted.
Output to be displayed : Done if succeed , Problem otherwise.
Possible Problem cases : No system, No line with <line_id>
---------------------------------------------------------------------------------------------------------------------
8. showLinesByStation <station_id>
display all line numbers that pass by station <station_id>. All ID numbers are displayed in 1 line,
sorted small to big left to right. Between every 2 adjacent numbers there appears a single
space. No spaces in start/end of the line. In the end of line go to start of next line.
If operation succeeds, then in the line after the output line Done is displayed as usual.
If the operation does not succeed, then no informative output of lines. Just display Problem, as
before.
Possible problem cases : No system, no station with <station_id>, memory problems etc.
----------------------------------------------------------------------------------------------------------------------
9. showSingleStations
display all IDs of stations such that no line pass by them.
If succeed, then all ID numbers of stations are displayed in 1 line sorted from small to big left to
right. 1 space only between every 2 adjacent numbers. no spaces in start/end of line. In end of
lines go to start of next line. Then display Done as usual. If no such stations at all, then go
immediately to start of next line. Then display Done as usual.
If operation fails, then Problem is to be displayed.
Possible Problem cases :
No system , memory problems (if relevant).
----------------------------------------------------------------------------------------------------------------------
10. showLine <Line_id>
display all stations IDs that appears in the line route. The ID numbers are displayed in 1 line
from left to right according to their order in the line route (1 direction). 1 space only between
every 2 adjacent numbers. no spaces in start/end of line. In end of lines go to start of next line.
Then display Done as usual.
If operation fails then Problem is displayed.
Possible Problem cases : No system, no line with <line_id>, memory problems (if relevant).
----------------------------------------------------------------------------------------------------------------------
11. showSystem
display the whole system.
The system name is displayed (from start of current line). Then go to start of next line.
Then All station ID numbers are displayed in 1 line small to big left to right. 1 space between
every 2 adjacent numbers. no spaces in start/end of line. In end of line go to start of next line.
Then display all ID numbers of lines in 1 line small to big left to right. 1 space between every 2
adjacent numbers. no spaces in start/end of line. In end of line go to start of next line. Then
display Done as usual. If no numbers to be displayed in any of the 2 informative lines (of
stations or lines) then go immediately to start of next line. For example, if there exist only
stations but no lines at all in the current system, then in first output line we get the IDs of
stations. Then we go to start of 2nd line and go immediately to start of 3rd line and display Done.
If operation fails then Problem is to be displayed.
Possible Problem cases : No system, memory problems (if relevant).
----------------------------------------------------------------------------------------------------------------------
Missions to be done in Part B :
1. Write the Station ADT (both Station.h and Station.c).
2. Write the Line ADT (both Line.h and Line.c).
3. Write the System ADT (both System.h and System.c).
4. Write a main program in a file operate.c
The program will get from standard input a series of textual commands (as described
before) and execute them. The output will be written into standard output.
 Can assume that all textual commands are legal. Each command appears in 1 line.
 No empty commands. No empty lines in input. names of commands are case sensitive
 (it’s important to distinguish between small letters and big letters). As described, in the
 end of executing every command we display either Done or Problem. No spaces at all
 and immediately after go to start of next line. Attached are the files
 operate_example_in.txt , operate_example_out.txt. Pay attention to have the EXACT
output format as appears in the given example files.
5. Run the program and check/verify that it is correct without BUGS and gives correct
output. In Part B no need to submit UNIT TESTS as in Part A. However, OF COURSE, IT’S
NECESSARY TO CHECK THE PROGRAM VERY CAREFULLY AND INTENSIVELY.
Remarks :
1. Pay attention to documentation. Especially in the h files. Concerning implementation
code, try to write it as self explanatory as possible. And short documentation in
meaningful code places.
2. Pay attention to all what we have learned – abstraction, encapsulation, avoiding
memory leak (use valgrind), check success of malloc, assert etc.
3. Can add more files than those mentioned before, according to needs.
4. Can use GSet and / or List from Part A, according to needs.
Compilation/Link is to be done as follows :
gcc -std=c99 -Wall -Werror -pedantic-errors -DNDEBUG -o operate.exe operate.c
System.c Line.c Station.c GSet.c List.c -L. –lmtm
Verify that the relevant library file libmtm.a is located in the current library.
If you’ve written more files in addition to those mentioned here, then, of course, you should
add them also in the compilation/link.
in Part B you should submit the following files :
Station.h Station.c
Line.h Line.c
System.h System.c
operate.c
and more files, if any, if you have written such.

Part C :
Write makefile as follows :
1. The command
make
will create the file operate.exe as described in Part B.
2. The command
make GSet_test.exe
will create the file GSet_test.exe as described in Part A.
3. The command
make GSet_test1.exe will create an executable file GSet_test1.exe in
the same way as GSet_test.exe is created but only one difference :
instead GSet_test.c we have here another program file GSet_test1.c.
Assume that this file exists in the current directory. (NO need to write it).
4. The command
make clean
will cause that if make command is executed afterwards then all relevant files
are re-compiled and then linked. (Build All).
Concerning the makefile, pay attention to have a readable makefile, easy to maintain and
having minimum duplication as possible.
in Part C you should submit the file :
makefile
