SELECT US.product_id, ROUND(SUM(P.price *  US.units)/SUM(US.units),2) as average_price
FROM UnitsSold US INNER JOIN Prices P ON 
    US.product_id = P.product_id AND
    US.purchase_date >= P.start_date AND
    US.purchase_date <= P.end_date
GROUP BY US.product_id;
