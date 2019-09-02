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
      //console.log(req)
      console.log(req.body)
      //controlModel.addDevice(req.body)
    },
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

