# Next Session Notes

Notes for next session on where I left off. I want to include things that didn't get done, where I stopped the session, and any bugs to worry about.

When writing notes put the next session notes above the previous so the most frequent notes apear on top.

## August 29, 2026

I need to add a new catagory to my packets for database status. Right now when a I complete a db_core operation I am returnign unimportant information that can be returned using function paramenters. I want to instead return the status of the database operation which I can use to determine errors that occur, state of the query, etc.
In addition to those two I am going to add two more categories, PayloadStatus these are not added to the packet these are internal statuses.

These is a lot more that needs done with the testing. In addition to all of the actual testing I need to go through and find instances of where I am using say the str_split funciton and check my result. If it is -1 handle accordingly via fprintf to stderr and returning PAYLOAD_STATUS_ERROR. The same needs done with the DbStatus (which I might change to DatabaseStatus) where I need to go through the program and implement my checks and bounds.

The largest refactor is going to be modifying all the original returns from those functions to be there new Statuses. This will involve modifying the parameters so I have out structs, and handling the actual errors themselves. Returning when something wrong happens I will need to specify in the fprintf to stderr. 

Lastly I will need to catch these errors and return whether a packet had an error in the Packet Status to make sure that the user is away that there way an issue with the packet. THe protocols I defined being BAD REQUEST or INTERNAL ERROR are dictated by what part of the program failed.

Lots of works ahead of you future Lukas good luck!

## August 28, 2026

I completed adding all the CRUD implementations to ever table with the exception of the read implementatin. 

What I need to do for the Read operation for standard table, tables with no relationships, is ask for the number of tables, and the offset. I can return a pagination struct and send it to the read operations on the server. The complex tables with many relationships are going to need to ask questions about what  filters they are looking for in addition to the offset and count.

I also started test files because I realized how valuable they actually are. I will be adding the implementation next before I complete the READ operation because then I can confirm everything works without manually testing. I can also garuantee minimal errors and the program works as intended.

TODO: (In this order)
- Complete basic testing implementation.
- Implement standard table read operation.
- Implement complex table read operation.

## August 27, 2026

Completed a lot of bug fixes but now the brand can be officially updated and deleted with the original create and info.

A new task that I need to complete is handling errors or edge cases, like infoing a record after deleting should return an obvious "DOES NOT EXIST".

All previous TODOs apply to next session.

## August 26, 2026

This issue with the get_string_input was inside of the normalization function. It was adding the offset to lowercase letters.

I got all the basic CRUD operation for Brand working except Read Many. This means I can just copy and paste the code from brand to all of the likewise tables (color, sleeves, condition, etc.).

TODO:
- And functionality to read_brands_input() functions. It should be simple to workd and not require any major functionality other than slightly different sequential questions and the result is a for loop over decoding the results + printing those decoded results.
- Fix segfaults (maybe?? It might just be the str_split that was broken and it works now.)
- Complete the Many Reads for multi relation tables.

## August 21, 2026

Completed fixing the join errors. It was an unnecessary function that I could have used the section we splot already instead of trying to rejoin a split string.

Something is wring with reading strings from user on client side. SOmething with trying to inline the string name with the get_string_input function. 
Start filling in the rest of the tables their basic CRUDs because brands work just need to go through and make them all similar. READ is a beast we will tackle depending on how we feel after filling in the rest of the functions.

TODO:
- Fix get_string_input to properly capture data
- Fix the segfaults on the server side for info (and probably others)
- Once those two are complete copy and paste the forat for the other basic tables.
- After those are done finish up with the Read functions

That should conclude a working MVP1.1 with MVP1.2 staring a better UI, testing, docs, and import/export.

## July 25, 2026

Complete 99% of errors for compiling the program. left with undefined join operation in the search functions.

Once those join operation get finished fcus on getting brands to go though the entire data pipeline before working on any other table. Get the user input, it sent to the client, the client handling it, data from the database, and back to the client. Do this for each crud operation and start with brand. Once you finish brand with the delete operation and the syntax is correct, it compiles, and works I can copy the logic to the rest of the tables. Repeat this for all the operations but stop before READ. READ should be your last operation because of the complexity with Pagination and Filters.
