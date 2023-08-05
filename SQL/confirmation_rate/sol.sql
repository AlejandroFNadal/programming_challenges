# https://leetcode.com/problems/confirmation-rate

SELECT spine.user_id, COALESCE(calculation.conf_rate, 0) as confirmation_rate
FROM(
    (
      SELECT Con.user_id, ROUND(SUM(CASE WHEN Con.action =  'confirmed' THEN 1 ELSE 0 END) / COUNT(*), 2) as conf_rate
      FROM Confirmations Con 
      GROUP BY Con.user_id
    ) calculation RIGHT JOIN (
        SELECT user_id
        FROM Signups sig
    ) spine ON calculation.user_id = spine.user_id
)
