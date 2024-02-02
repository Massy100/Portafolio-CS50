-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Show tables
.tables
-- Show schema of crime scene reports
.schema crime_scene_reports
-- Find crime scene description
SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28
AND street = 'Humphrey Street';
-- Now I know the crime was during 10:15 am at th bakery and there was 3 witnesses
-- Find the lincense plates on the bakery security logs
SELECT license_plate
FROM bakery_security_logs
WHERE month = 7 AND day = 28
AND hour >= 10 AND hour < 11
AND activity = 'entrance';
-- Now I have 5 license plates and one of the might be the thief
-- Find the transcripts of the interviews
SELECT transcript
FROM interviews
WHERE month = 7 AND day = 28;
-- Now I know the thief left 10 minutes after the theft in a car, the thief withdrawned some money at the ATM
--before the theft and when the thief left he called someone in less than a minute, he was planning to take a
-- flight the next day and he asked the person to buy the ticket
-- Find the account number of the atm transactions
SELECT account_number
FROM atm_transactions
WHERE month = 7 AND day = 28
AND atm_location = 'Humphrey Lane'
AND transaction_type = 'withdraw';
-- Now I have several account numbers and one of them must be from the thief
-- Find the id from the airport
SELECT id
FROM airports
WHERE full_name = 'Fiftyville Regional Airport';
-- Now I known the airport id is 8
-- Find the destination airport from the flights
SELECT destination_airport_id
FROM flights
WHERE month = 7 AND day = 29
AND origin_airport_id = 8;
-- Now I know there were 5 flights that day, with ids: 6 11 4 1 9
-- Find the airport name from airports
SELECT full_name
FROM airports
WHERE id IN (6, 11, 4, 1, 9);
-- Now I know the 5 cities where he might escaped
-- Find the id of the flight
SELECT id
FROM flights
WHERE month = 7 AND day = 29
AND origin_airport_id = 8;
-- Now I know the ids: 18 23 36 43 53
-- Find passport number from passengers
SELECT passport_number
FROM passengers
WHERE flight_id IN (18, 23, 36, 43, 53);
-- Find the caller and the receiver from phone calls
SELECT caller, receiver
FROM phone_calls
WHERE month = 7 AND day = 28
AND duration <= 60;
-- Now I have 10 phone numbers from the caller and the receiver
-- Find the thief
SELECT name
FROM people
WHERE
  license_plate IN ('R3G7486', '13FNH73', 'NRYN856', 'WD5M8I6', 'V47T75I') AND
  phone_number IN (
    '(130) 555-0289', '(499) 555-9472', '(367) 555-5533', '(609) 555-5876', '(499) 555-9472',
    '(286) 555-6063', '(770) 555-1861', '(031) 555-6622', '(826) 555-1652', '(338) 555-6650'
  ) AND
  passport_number IN (
    2835165196, 6131360461, 3231999695, 3592750733, 2626335085, 6117294637, 2996517496, 39156221712,
    4149859587, 9183348466, 7378796210, 7874488539, 4195341387, 6263461050, 3231999695, 7951366683,
    7214083635, 1695452385, 5773159633, 1540955065, 8294398571, 1988161715, 9878712108, 8496433585,
    7597790505, 6128131458, 6264773605, 3642612721, 4356447308, 74411335547, 7894166154, 6034823042,
    4408372428, 2312901747, 1151340634, 8174538026, 1050247273, 7834357192
  );
-- The thief Bruce
-- Find the accomplice
SELECT name
FROM people
WHERE phone_number IN ('(996) 555-8899', '(892) 555-8872', '(375) 555-8161', '(389) 555-5198', '(717) 555-1342', '(676) 555-6554', '(725) 555-3243', '(910) 555-3251', '(066) 555-9701', '(704) 555-2131');
-- The accomplice is Robin




