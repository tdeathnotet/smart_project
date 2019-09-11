import {controlModel} from './index' 

var tvButton 
var fanButton 
var airButton 

var decode_TV 
var checkStatus

const controller = {
    decodeTVRemote(req,res){
      var decode = req.body.button
      
      checkStatus = req.body.status
      console.log(req.body.status)
      console.log(req.body.button)  //โชว์ปุ่มที่ต้องการ Decode

      if(decode == "decode_tvOn_Off" ){
        decode_TV = "tv_On"
      }else if(decode == "decode_tvUp") {
        decode_TV = "tv_Up"
      }else if(decode == "decode_tvDown") {
        decode_TV = "tv_Down"
      }else if(decode == "decode_tvLeft") {
        decode_TV = "tv_Left"
      }else if(decode == "decode_tvRight") {
        decode_TV = "tv_Right"
      }else if(decode == "decode_tvOk") {
        decode_TV = "tv_OK"
      }else if(decode == "decode_tvVol_up") {
        decode_TV = "tv_volUp"
      }else if(decode == "decode_tvVol_down") {
        decode_TV = "tv_VolDown"
      }else if(decode == "decode_tvCh_up") {
        decode_TV = "tv_CHUp"
      }else if(decode == "decode_tvCh_down") {
        decode_TV = "tv_CHDown"
      }else if(decode == "decode_tvReturn") {
        decode_TV = "tv_Return"
      }else if(decode == "decode_tvMute") {
        decode_TV = "tv_Mute"
      }else;

    }, 
    decodeTVbutton(req,res){
      res.status(200).json({ "Button" : decode_TV ,"Status" : checkStatus })
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
        airButton = "air_power"
        //setTimeout(function(){ fanButton = "0" }, 100)
      }else if(check == "airFanSpeed"){
        airButton = "air_speedFan"
        //setTimeout(function(){ fanButton = "0" }, 100)
      }else if(check == "airTempUp"){
        airButton = "air_tempUp"
        //setTimeout(function(){ fanButton = "0" }, 100)
      }else if(check == "airTempDown"){
        airButton = "air_tempDown"
        //setTimeout(function(){ fanButton = "0" }, 100)
      }
      else{
        tvButton = "0"
        fanButton = "0"
        airButton = "0"
      }
    },
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
      const reqTVButton = req.params.button //รับค่าจาก url เป็น params

      var buffTVButton = reqTVButton+"Buff"  //เพิ่มString Buff เพิ่แไปเช็คค่าในตาราง tv_OnBuff
      //console.log(reqButton , buffButton)
      controlModel.getTV_remote(reqTVButton,buffTVButton).then((rawData) => {    //ส่งข้อมูลจาก getName(temp) กลับมาแสดงจาก Database
        res.status(200).send(rawData)
        //console.log(rawData)
      })
    },
    getACRemote(req,res){
      const reqACButton = req.params.button //รับค่าจาก url เป็น params

      var buffACButton = reqACButton+"Buff"  //เพิ่มString Buff เพิ่แไปเช็คค่าในตาราง tv_OnBuff
      //console.log(reqButton , buffButton)
      controlModel.getAC_remote(reqACButton,buffACButton).then((rawData) => {    //ส่งข้อมูลจาก getName(temp) กลับมาแสดงจาก Database
        res.status(200).send(rawData) 
        //console.log(rawData)
      })
    },    
    getFanRemote(req,res){
      const reqFanButton = req.params.button //รับค่าจาก url เป็น params

      var buffFanButton = reqFanButton+"Buff"  //เพิ่มString Buff เพิ่แไปเช็คค่าในตาราง tv_OnBuff
      //console.log(reqButton , buffButton)
      controlModel.getFan_remote(reqFanButton,buffFanButton).then((rawData) => {    //ส่งข้อมูลจาก getName(temp) กลับมาแสดงจาก Database
        res.status(200).send(rawData) 
        //console.log(rawData)
      })
    },
    getButtonFan(req,res){
      res.json({"Button": fanButton })

    },
    getButtonTV(req,res){
      res.json({"Button" : tvButton })
    },
    getButtonAC(req,res){
      res.json({"Button" : airButton })
    }
          
    
}
export default controller 
