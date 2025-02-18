# Project 2: DSV & XML Parsing Project
By: Paul Le 

## What Works & What Doesn't
 DSV (Delimiter-Separated Values) Stuff:
- DSV Reader is working - it can read CSV files and split them into rows/columns correctly
- DSV Writer also works - can write data into CSV format properly

 XML Parser Issues:
- Ran into some major headaches with the XML part
- Main problem was with Expat library compatibility - kept getting DLL errors that we couldn't resolve 
- XML functionality is there but not fully operational

## Known Issues & Limitations
- XML Reader crashes because of DLL/compatibility stuff
- Focused on making sure the DSV part works solidly instead of fighting with XML
- If you need to parse XML, you'll want to use a different implementation

## Building & Testing
- Use `make all` to build everything
- Use `make test` to run the tests (DSV tests should pass)
- XML tests are included but might not run due to library issues

## Development Notes
- Written in C++ following the project specs
- Used GoogleTest for testing (though local testing was tricky)
- Implemented proper memory management with smart pointers
- Made sure to handle edge cases in DSV parsing (quotes, delimiters in data, etc.)

## Final Notes
Got the core DSV functionality working solidly, but XML gave us problems with dependencies and DLL stuff. Rather than having partially broken XML code, we focused on making sure the DSV part was robust and well-tested. The XML implementation is there but needs more work to be fully functional.