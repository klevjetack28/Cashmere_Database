# Next Session Notes

Notes for next session on where I left off. I want to include things that didn't get done, where I stopped the session, and any bugs to worry about.

When writing notes put the next session notes above the previous so the most frequent notes apear on top.

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
