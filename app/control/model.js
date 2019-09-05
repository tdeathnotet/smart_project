//'user strict';
var sql = require('../db');
import pool from '../db' 

const controlModel = {
    getName(name){
        return new Promise((resolve,reject) => {
            pool.query('SELECT * FROM `devices` WHERE `device_id` = ?',[name],
            function (error, results, fields) {
                if (error) throw error;
                    console.log(results)
                    return resolve(results)
            }
            )
        }) //callback function
    },
    createUser(users){
        
        return new Promise ((resolve , reject) =>{
            pool.query('INSERT INTO `devices`(`device_name`, `device_room`, `wifi_user`, `wifi_pass`) VALUES ? ',[users],
            function(error,results,fields){
                if(error) throw error;
                console.log(results)
                return resolve(results)
            })
        })
    },
    insertTest(temp){
        return new Promise((resolve , reject) => {
            //const tem = { air_power: 'Winnie', air_tempUp: 'Australia' };
            pool.query('INSERT INTO `remote_air`(air_power,air_tempUp) VALUES (?,?)',[temp,temp], 
            function(err,result,fields){
                if(err) throw err;
                console.log("1 record ")
                return resolve(result)
            })
        })
    },
    addTV_remote({tv_On}){
        return new Promise((resolve , reject) => {
            //const tem = { air_power: 'Winnie', air_tempUp: 'Australia' };
            pool.query('INSERT INTO `tv_remote` (On) VALUES (?)',[tv_On], 
            function(err,result,fields){
                if(err) throw err;
                console.log("1 record ")
                return resolve(result)
            })
        })
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

