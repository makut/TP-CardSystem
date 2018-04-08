# TP-CardSystem
Universal card system.
The designed of the terminal should write his own class Terminal, which is of interface ITerminal. So it allows to read the card from the terminal.
Having the card objects, we can use abilities of Services (or Managers). In this API we have a Service and a Manager for getting passport information and a Service for operations between accounts.
The PassportManager is a proxy of PassportService, which saves information into cache, and so it's desirable to use PassportManager in the since it works faster and doesn't executes excess requests to the server.

