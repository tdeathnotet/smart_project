import {controlModel} from './index' 


const controller = {

    showTemp(req,res){
      //console.log(req)
      const t = req.query.temp
      console.log(t)
      //res.send('success : ' + t)

      controlModel.insertTest(t)
      
      //controlModel.showTemp(t).then(data)
      // const t = req.body.temp
      // console.log(t)
      // res.send(req.body)
    },
    showJson(req,res){
      console.log(req.body)
      //console.log(JSON.stringify(j))
     controlModel.addDevice(req.body)
    },
  //   createUser(req,res){
  //     // const { 
  //     //   device_name,
  //     //   device_room,
  //     //   wifi_user,
  //     //   wifi_pass } = req.body //รับค่า
  //     const data = {
  //       name,
  //       room,
  //       wifi_name,
  //       wifi_pass } = req.body
        
  //       res.status(201).json(data)

        

  //   //res.status(200).json(data)
  //  //รับค่า
  //   //     const temp = req.users.temp
  //   //     //
  //   // controlModel.createUser(
  //   //   device_name,
  //   //   device_room,
  //   //   wifi_user,
  //   //   wifi_pass ).then(controlModel => {
  //   //     res.status(201).json(controlModel)
  //   //   })
  //   },

    getName(req,res){
      const reqID = req.params.id //รับค่าจาก url เป็น params
      //const reqID = req.name
      console.log(reqID)
      controlModel.getName(reqID).then((data) => {  //ส่งข้อมูลจาก getName(temp) กลับมาแสดงจาก Database
        res.status(200).json({ "device_name": data }) 
      //res.status(200).json({ "device_name": "Suchada", "device_room": "Bedroom" })
      })     
    }
}
export default controller 



/*'user strict';

var Customer = require('../appModel.js/index.js');

exports.list_all_customers = function(req,res){
    Customer.getAllCustomer(function(err,customer_fullName){
        console.log('Controller')
        if(err)
            res.send(err);
            console.log('res',customer_fullName);
        res.send(customer_fullName);
    });
};

exports.create_a_customer = function(req, res) {
  var new_customer = new Customer(req.body);

  //handles null error 
   if(!new_customer.customer_fullName || !new_customer.status){

            res.status(400).send({ error:true, message: 'Please provide customers/status' });

    }else{
        Customer.createCustomer(new_customer, function(err, customer_fullName) {
    
        if (err)
            res.send(err);
        res.json(customer_fullName);
    });
    }
};


exports.read_a_customer = function(req, res) {
    Customer.getCustomerById(req.params.customer_id, function(err, customer_fullName) {
    if (err)
      res.send(err);
    res.json(customer_fullName);
  });
};


exports.update_a_customer = function(req, res) {
    Customer.updateById(req.params.customer_id, new Customer(req.body), function(err, customer_fullName) {
    if (err)
      res.send(err);
    res.json(customer_fullName);
  });
};


exports.delete_a_customer = function(req, res) {

  Customer.remove( req.params.customer_id, function(err,customer_fullName) {
    if (err)
      res.send(err);
    res.json({ message: 'Customer successfully deleted' });
  });
};

*/

