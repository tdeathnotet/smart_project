import {controlModel} from './index' 

var tvButton ="";
var fanButton ="";
var airButton = "";

const controller = {
    addTVRemote(req,res){  // add TV remote
      //console.log(req.body)
      controlModel.addTV_remote(req.body)
    },
    addACRemote(req,res){  // add AC remote
      //console.log(req.body)
      controlModel.addAC_remote(req.body)
    },
    addFanRemote(req,res){  // add AC remote
      //console.log(req.body)
      controlModel.addFan_remote(req.body)
    },
    getTVRemote(req,res){
      const reqButton = req.params.button //รับค่าจาก url เป็น params
      //const reqID = req.name
      var buffButton = reqButton+"Buff"  //เพิ่มString Buff เพิ่แไปเช็คค่าในตาราง tv_OnBuff
      
      console.log(reqButton , buffButton)
      controlModel.getTV_remote(reqButton,buffButton).then((rawData) => {    //ส่งข้อมูลจาก getName(temp) กลับมาแสดงจาก Database
        res.status(200).send(rawData) //res.status(200).json({ "device_name": "Suchada", "device_room": "Bedroom" })
        //console.log(rawData)
      })
    },
    getButtonTV(req,res){
      res.json({"Button": tvButton })
    },

    ButtonOnPost(req, res){
      var check = req.body.button
      console.log(req.body.button)

//________________________TV Control____________________________________
      if(check == "tvOn_Off" ){
        tvButton = "tv_On"
        setTimeout(function(){ tvButton = "0" }, 100)
      }else if(check == "tvUp") {
        tvButton = "tv_Up"
        setTimeout(function(){ tvButton = "0" }, 100)
      }else if(check == "tvDown") {
        tvButton = "tv_Down"
        setTimeout(function(){ tvButton = "0" }, 100)
      }else if(check == "tvLeft") {
        tvButton = "tv_Left"
        setTimeout(function(){ tvButton = "0" }, 100)
      }else if(check == "tvRight") {
        tvButton = "tv_Right"
        setTimeout(function(){ tvButton = "0" }, 100)
      }else if(check == "tvOk") {
        tvButton = "tv_OK"
        setTimeout(function(){ tvButton = "0" }, 100)
      }else if(check == "tvVol_up") {
        tvButton = "tv_volUp"
        setTimeout(function(){ tvButton = "0" }, 100)
      }else if(check == "tvVol_down") {
        tvButton = "tv_VolDown"
        setTimeout(function(){ tvButton = "0" }, 100)
      }else if(check == "tvCh_up") {
        tvButton = "tv_CHUp"
        setTimeout(function(){ tvButton = "0" }, 100)
      }else if(check == "tvCh_down") {
        tvButton = "tv_CHDown"
        setTimeout(function(){ tvButton = "0" }, 100)
      }else if(check == "tvReturn") {
        tvButton = "tv_Return"
        setTimeout(function(){ tvButton = "0" }, 100)
      }else if(check == "tvMute") {
        tvButton = "tv_Mute"
        setTimeout(function(){ tvButton = "0" }, 100)
//______________________________FAN Control__________________________________________________
      }else if(check == "fanOn_Off"){ 
        fanButton = "fan_On"
        setTimeout(function(){ fanButton = "0" }, 100)
      }else if(check == "fanSpeed"){
        fanButton = "fan_Speed"
        setTimeout(function(){ fanButton = "0" }, 100)
      }else if(check == "fanSwing"){
        fanButton = "fan_Swing"
        setTimeout(function(){ fanButton = "0" }, 100)
//_______________________________Air Control_________________________________________________
      }else if(check == "airPower"){
        fanButton = "air_power"
        //setTimeout(function(){ fanButton = "0" }, 100)
      }else if(check == "airFanSpeed"){
        fanButton = "air_speedFan"
        //setTimeout(function(){ fanButton = "0" }, 100)
      }else if(check == "airTempUp"){
        fanButton = "air_tempUp"
        //setTimeout(function(){ fanButton = "0" }, 100)
      }else if(check == "airTempDown"){
        fanButton = "air_tempDown"
        //setTimeout(function(){ fanButton = "0" }, 100)
      }
      else{
        tvButton = "0"
        fanButton = "0"
      }
      

      // res.status(400).json(req.body)
      //res.json(req.body)
      // //TvOn = req.body.button;
    },
    getButtonFan(req,res){
      res.json({"Button": fanButton })

    },
    addFanOnPost(req,res){
      res.json({"Button": airButton })
    }
          
    
}
export default controller 
