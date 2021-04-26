-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Look at the interviews for that day
SELECT id, name, transcript
FROM interviews
WHERE year = 2020
AND month = 7
AND day = 28;

-- Follow Ruth's hint:
-- Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away.
-- If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.

-- Get the time of the incident
SELECT *
FROM crime_scene_reports
WHERE year = 2020
AND month = 7
AND day = 28;
-- Chamberlin Street | Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.

-- Look at license plate numbers 10 witihn 10 minutes of the theft
SELECT license_plate
FROM courthouse_security_logs
WHERE year = 2020
AND month = 7
AND day = 28
AND hour = 10
AND minute > 15
AND minute < 25;
-- 5P2BI95
-- 94KL13X
-- 6P58WS2
-- 4328GD8
-- G412CB7
-- L93JTIZ
-- 322W7JE
-- 0NTHK55

-- Get people who have these cars
SELECT *
FROM people
WHERE license_plate IN (
    SELECT license_plate
    FROM courthouse_security_logs
    WHERE year = 2020
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute > 15
    AND minute < 25
);

-- Follow Eugene's Hint
-- I don't know the thief's name, but it was someone I recognized. Earlier this morning,
-- before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the
-- thief there withdrawing some money.

-- Get account numbers of all withdrawls in time frame
SELECT account_number
FROM atm_transactions
WHERE year = 2020
AND month = 7
AND day = 28
AND transaction_type = "withdraw"
AND atm_location = "Fifer Street";
-- 28500762
-- 28296815
-- 76054385
-- 49610011
-- 16153065
-- 25506511
-- 81061156
-- 26013199

-- Get people who have these account numbers AND own a car from the previous list
SELECT *
FROM people
WHERE id IN (
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE year = 2020
        AND month = 7
        AND day = 28
        AND transaction_type = "withdraw"
        AND atm_location = "Fifer Street"
    )
)
AND license_plate IN (
    SELECT license_plate
    FROM courthouse_security_logs
    WHERE year = 2020
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute > 15
    AND minute < 25
);


-- Follow Raymond's Hint
-- As the thief was leaving the courthouse, they called someone who talked to them for less than a minute.
-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- Get phone calls under a minute after the incident
SELECT caller
FROM phone_calls
WHERE year = 2020
AND month = 7
AND day = 28
AND duration < 60;
-- (130) 555-0289
-- (499) 555-9472
-- (367) 555-5533
-- (499) 555-9472
-- (286) 555-6063
-- (770) 555-1861
-- (031) 555-6622
-- (826) 555-1652
-- (338) 555-6650

-- Get people who have these Phone number AND account numbers AND own a car from the previous list
SELECT *
FROM people
WHERE phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE year = 2020
    AND month = 7
    AND day = 28
    AND duration < 60
)
AND id IN (
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE year = 2020
        AND month = 7
        AND day = 28
        AND transaction_type = "withdraw"
        AND atm_location = "Fifer Street"
    )
)
AND license_plate IN (
    SELECT license_plate
    FROM courthouse_security_logs
    WHERE year = 2020
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute > 15
    AND minute < 25
);


-- Continue with Raymond's Hint, look for the first flight out of Fiftyville on the day after the incident
SELECT passport_number
FROM passengers
WHERE flight_id = (
    SELECT id
    FROM flights
    WHERE origin_airport_id IN (
        SELECT id
        FROM airports
        WHERE city = "Fiftyville"
    )
    AND year = 2020
    AND month = 7
    AND day = 29
    ORDER BY hour
    LIMIT 1
);

-- Match passenger passports with remaining people
SELECT *
FROM people
WHERE phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE year = 2020
    AND month = 7
    AND day = 28
    AND duration < 60
)
AND id IN (
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE year = 2020
        AND month = 7
        AND day = 28
        AND transaction_type = "withdraw"
        AND atm_location = "Fifer Street"
    )
)
AND license_plate IN (
    SELECT license_plate
    FROM courthouse_security_logs
    WHERE year = 2020
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute > 15
    AND minute < 25
)
AND passport_number IN (
    SELECT passport_number
    FROM passengers
    WHERE flight_id = (
        SELECT id
        FROM flights
        WHERE origin_airport_id IN (
            SELECT id
            FROM airports
            WHERE city = "Fiftyville"
        )
        AND year = 2020
        AND month = 7
        AND day = 29
        ORDER BY hour
        LIMIT 1
    )
);

-- Get destination airport
SELECT *
FROM airports
WHERE id = (
    SELECT destination_airport_id
    FROM flights
    WHERE origin_airport_id IN (
        SELECT id
        FROM airports
        WHERE city = "Fiftyville"
    )
    AND year = 2020
    AND month = 7
    AND day = 29
    ORDER BY hour
    LIMIT 1
)



-- Continue with Raymond's hint
-- Get the receiver of the call
SELECT *
FROM people
WHERE phone_number IN (
    SELECT receiver
    FROM phone_calls
    WHERE year = 2020
    AND month = 7
    AND day = 28
    AND duration < 60
    AND caller = (
        SELECT phone_number
        FROM people
        WHERE phone_number IN (
            SELECT caller
            FROM phone_calls
            WHERE year = 2020
            AND month = 7
            AND day = 28
            AND duration < 60
        )
        AND id IN (
            SELECT person_id
            FROM bank_accounts
            WHERE account_number IN (
                SELECT account_number
                FROM atm_transactions
                WHERE year = 2020
                AND month = 7
                AND day = 28
                AND transaction_type = "withdraw"
                AND atm_location = "Fifer Street"
            )
        )
        AND license_plate IN (
            SELECT license_plate
            FROM courthouse_security_logs
            WHERE year = 2020
            AND month = 7
            AND day = 28
            AND hour = 10
            AND minute > 15
            AND minute < 25
        )
        AND passport_number IN (
            SELECT passport_number
            FROM passengers
            WHERE flight_id = (
                SELECT id
                FROM flights
                WHERE origin_airport_id IN (
                    SELECT id
                    FROM airports
                    WHERE city = "Fiftyville"
                )
                AND year = 2020
                AND month = 7
                AND day = 29
                ORDER BY hour
                LIMIT 1
            )
        )
    )
);