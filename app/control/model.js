//'user strict';
var sql = require('../db');
import pool from '../db' 

const controlModel = {
    addTV_remote({column, value}){
        console.log({column,value})
        return new Promise((resolve , reject) => {
            //const tem = { air_power: 'Winnie', air_tempUp: 'Australia' };
            pool.query('UPDATE `tv_remote` SET '+column+' = ?' ,[value], 
            function(err,result,fields){
                if(err) throw err;
                console.log("UPDATE " + column)
                return resolve(result)
            })
        })
    },
    getTV_remote(column){
        return new Promise((resolve,reject) => {
            pool.query('SELECT '+column+' FROM `tv_remote`',
            function (error, results, fields) {
                if (error) throw error;
                    // console.log(results)
                    return resolve(results)
            }
            )
        }) //callback function
    }
}

export default controlModel

//Task object constructor
/*var Customer = function(customer){
    this.customer_fullName = customer.customer_fullName;
    this.customer_email = customer.customer_email;
    this.status = customer.status;
    this.customer_password = customer.customer_password;
    this.customer_phone = customer.customer_phone;
    this.created_At = new Date();
};
Customer.createCustomer = function(newCustomer, result){

    sql.query("INSERT INTO customers set ?",newCustomer,function(err,res){
        if(err){
            console.log("error: ",err);
            result(err,null);
        }else{
            console.log(res.insertId);
            result(null,res.insertId);
        }
    });
};
Customer.getCustomerById = function(customerId,result){
    sql.query("Select customer_fullName from customers where customer_id = ? ", customerId, function (err, res) {             
        if(err) {
            console.log("error: ", err);
            result(err, null);
        }
        else{
            result(null, res);
        }
    });   
};
Customer.getAllCustomers = function (result) {
    sql.query("Select * from customers", function (err, res) {

            if(err) {
                console.log("error: ", err);
                result(null, err);
            }
            else{
              console.log('customers : ', res);  

             result(null, res);
            }
        });   
};
Customer.updateById = function(customer_id,customer,result){
    sql.query("UPDATE customers SET customer_fullName = ? WHERE customer_id = ?", [customer.customer_fullName,customer_id],function(err,res){
        if(err){
            console.log("error: ",err);
            result(null,err);
        }else{
            result(null,res);
        }
    });
};
Customer.remove = function(customer_id,result){
    sql.query("DELETE FROM customers WHERE customer_id = ?", [customer_id],function(err,res){
        if(err){
            console.log("error",err);
            result(null,err);
        }else{
            result(null,res);
        }
    });
};

module.exports = Customer;
*/

