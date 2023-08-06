# Write your MySQL query statement below
SELECT ROUND(COUNT(first_orders.customer_id)*100 / (SELECT COUNT(DISTINCT(customer_id)) from Delivery),2) as immediate_percentage
FROM Delivery D1 INNER JOIN (
    SELECT customer_id, MIN(order_date) as order_Date 
    FROM Delivery D 
    GROUP BY customer_id
) first_orders ON D1.customer_id = first_orders.customer_id AND
    D1.order_date = first_orders.order_date AND
    first_orders.order_date = D1.customer_pref_delivery_date
