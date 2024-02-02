import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, is_int

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        # Ensure symbol and shares are provided
        symbol = request.form.get("symbol")
        shares_str = request.form.get("shares")

        if symbol == "":
            return apology("MISSING SYMBOL", 400)
        if shares_str == "" or shares_str.isalpha():
            return apology("MISSING SHARES", 400)
        if not is_int(shares_str):
            return apology("fractional not supported", 400)
        if int(shares_str) <= 0:
            return apology("share number can't be negative number or zero!", 400)

        # Get current stock quote
        quote = lookup(symbol)

        if quote is None:
            return apology("invalid stock symbol", 400)

        # Calculate the total cost of the transaction
        total_cost = quote["price"] * shares

        # Get user's cash balance
        user_id = session["user_id"]
        user = db.execute("SELECT * FROM users WHERE id = ?", user_id)[0]
        cash_balance = user["cash"]

        # Check if the user has enough cash to make the purchase
        if cash_balance < total_cost:
            return apology("insufficient funds", 403)

        # Deduct the total cost from the user's cash balance
        new_cash_balance = cash_balance - total_cost
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash_balance, user_id)

        # Record the transaction in the users table
        db.execute(
            "UPDATE users SET cash = ?, stocks = stocks || ? WHERE id = ?",
            new_cash_balance,
            f",{symbol}:{shares}",
            user_id,
        )

        flash("Purchase successful!")
        # Redirect to the index page
        return redirect("/")

    else:
        # If the request method is GET, render the buy.html template
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Get user's transaction history
    user_id = session["user_id"]
    transactions = db.execute(
        "SELECT symbol, transaction_type, price, shares, timestamp FROM transactions WHERE user_id = ? ORDER BY timestamp DESC",
        user_id,
    )

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":
        # Ensure symbol is provided
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("must provide stock symbol", 400)

        # Get current stock quote
        quote = lookup(symbol)

        if quote is None:
            return apology("invalid stock symbol", 400)

        # Render the quote.html template with the stock quote information
        return render_template("quote.html", quote=quote)

    else:
        # If the request method is GET, render the quote.html template
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        # Ensure username, password, and password confirmation are provided
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username or not password or not confirmation:
            return apology("all fields must be filled", 400)

        # Ensure password and confirmation match
        if password != confirmation:
            return apology("passwords do not match", 400)

        # Generate hash for the password
        hashed_password = generate_password_hash(password)

        # Insert the new user into the users table
        result = db.execute(
            "INSERT INTO users (username, hash) VALUES (?, ?)",
            username,
            hashed_password,
        )

        # Check if username is already taken
        if not result:
            return apology("username already taken", 400)

        # Log in the newly registered user
        user_id = db.execute("SELECT id FROM users WHERE username = ?", username)[0][
            "id"
        ]
        session["user_id"] = user_id

        # Redirect to the index page
        return redirect("/")

    else:
        # If the request method is GET, render the register.html template
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # Get user's stock holdings
    user_id = session["user_id"]
    user = db.execute("SELECT * FROM users WHERE id = ?", user_id)[0]
    stocks = user["stocks"]

    if request.method == "POST":
        # Ensure stock symbol and shares are provided
        symbol = request.form.get("symbol")
        shares_str = request.form.get("shares")

        if not symbol:
            return apology("must select a stock", 400)

        if not shares_str or not shares_str.isdigit():
            return apology("invalid number of shares", 400)

        shares = int(shares_str)

        # Check if the user owns the selected stock
        if not stocks or stocks.get(symbol, 0) < shares:
            return apology("insufficient shares", 400)

        # Get current stock quote
        quote = lookup(symbol)

        if quote is None:
            return apology("invalid stock symbol", 400)

        # Calculate the total earnings from the sale
        total_earnings = quote["price"] * shares

        # Update user's cash balance
        new_cash_balance = user["cash"] + total_earnings
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash_balance, user_id)

        # Update user's stock holdings
        new_stocks = {k: v - shares if k == symbol else v for k, v in stocks.items()}
        db.execute("UPDATE users SET stocks = ? WHERE id = ?", new_stocks, user_id)

        flash("Sale successful!")
        # Redirect to the home page
        return redirect("/")

    else:
        # If the request method is GET, render the sell.html template with stock symbols
        return render_template("sell.html", stocks=stocks)
