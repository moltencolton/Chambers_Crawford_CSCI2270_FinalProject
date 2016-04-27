# C++ Quote Verifier 

### Project Summary 
This project uses [Wikiquote](https://www.wikiquote.org/) to allow the user to get the quotes of various people. This is accomplished by using cURL to get the HTML of the Wikiquote page for that person and then parsing the quotes into a usable format. Once these quotes have been parsed out, they are stored in a binary search tree for easy searching. This can be used to check if quotes found online for this person are real, or if they could be made up.

### How to Run
1. Create the object files and executable with `$ make`
2. Run the executable with `$ ./QuoteVerifier`

Note: if changes to the code do not show up after calling `$ make`, try running `$ make clean` before to start with fresh object files and executable.

#####Program Options
  
1. Get Quote Data
  - Retrieves the data from Wikiquote and store the quotes in the binary search tree if found. Must be called before selecting other options that require the quote data.
2. Verify a Quote
  - Prompts for a quote and searches the given data for the quote. Note: this works best with fragments of quotes, rather than entire quotes.
3. List All Quotes
  - Lists all quotes found on Wikiquote by the given author.
4. Count Quotes
  - Gives the number of quotes found on Wikiquote by the given author.
5. Get a Random Quote
  - Selects a random quote from the binary search tree and displays it to the user.
6. Get Current Author
  - Displays which author's data is currently stored in the binary search tree.
7. Check For Author
  - Checks for given author's presence on Wikiquote.

### Dependencies
- cURL
- [libcurl](https://curl.haxx.se/libcurl/)

Note: these packages come included in the [CU CS Virtual Machine](https://foundation.cs.colorado.edu/vm/) and the package flag in the makefile is designed to work for this system. If you are using the [CU CS Virtual Machine](https://foundation.cs.colorado.edu/vm/), you should not have to do any extra installations. 

### System Requirements
- Linux based OS
- Internet Connection

###Group members
- [Jacob Crawford](https://github.com/JakeC1020)
- [Colton Chambers](https://github.com/moltencolton)

###Contributors

###Bugs/Enhancement Requests
- [Accept Wider Range of Author Names](https://github.com/moltencolton/Chambers_Crawford_CSCI2270_FinalProject/issues/5)
- [General Polishing](https://github.com/moltencolton/Chambers_Crawford_CSCI2270_FinalProject/issues/6)

###Attributions
- Recieved general C++ help from [Boskin Erkocevic](https://github.com/Boskin)
- Recieved general C++ help from [Evan Su](https://github.com/hexacyanide)
- Referenced [http://www.cplusplus.com/reference/](http://www.cplusplus.com/reference/)

#####Modified code from following locations:
- [http://stackoverflow.com/questions/11625759/how-to-properly-install-libcurl-and-link-it-to-a-c-program](http://stackoverflow.com/questions/11625759/how-to-properly-install-libcurl-and-link-it-to-a-c-program)
- [http://stackoverflow.com/questions/9786150/save-curl-content-result-into-a-string-in-c](http://stackoverflow.com/questions/9786150/save-curl-content-result-into-a-string-in-c)
- [http://www.cplusplus.com/forum/unices/45878/](http://www.cplusplus.com/forum/unices/45878/)
