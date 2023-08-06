ELECT CONCAT(
    EXTRACT(YEAR from T.trans_date),
    "-",
    LPAD(
        EXTRACT(MONTH from T.trans_date),
        2,
        "0"
    )
) as month,T.country, count(*) as trans_count,
SUM(CASE WHEN T.state = "approved" THEN 1 ELSE 0 END) as approved_count,
SUM(T.amount) as trans_total_amount,
SUM(CASE WHEN T.state = "approved" THEN T.amount ELSE 0 END) as approved_total_amount
FROM Transactions T
GROUP BY month, T.country
