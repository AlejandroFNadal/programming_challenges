SELECT Q.query_name, 
    ROUND(AVG(Q.rating/Q.position),2) as quality, 
    ROUND(SUM(CASE WHEN Q.rating < 3 THEN 1 ELSE 0 END)*100/COUNT(*),2) as poor_query_percentage
FROM Queries Q
GROUP BY query_name
