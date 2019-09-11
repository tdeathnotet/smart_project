import controller from './controller'


export function setup(router){
    router.post('/remote/button_on_post',controller.ButtonOnPost) //เก็บค่าปุ่มจาก หน้าบ้าน...
    

    //________________________DECODE TV REMOTE___________________________
    router.post('/api/remote_tv',controller.addTVRemote)
    router.post('/remote/decode/tv_remote',controller.decodeTVRemote)  //หน้าบ้านส่งปุ่มอะไรมา
    router.get('/remote/decode/tv_button',controller.decodeTVbutton)  //ส่งให้ ESP8266


    //________________________DECODE AC REMOTE___________________________
    router.post('/api/remote_ac',controller.addACRemote)
    



    //________________________DECODE FAN REMOTE__________________________
    router.post('/api/remote_fan',controller.addFanRemote)
    

    //--------------------------------------------TV---------------------------------
    router.get('/remote_tv/button',controller.getButtonTV)
    router.get('/tv/:button',controller.getTVRemote)
    // router.post('/remote_tv/tv_On_post',controller.addTvOnPost)
    //--------------------------------------------FAN--------------------------------
    router.get('/remote_fan/button',controller.getButtonFan)
    router.get('/fan/:button',controller.getFanRemote)
    //-------------------------------------------AC----------------------------------
    router.get('/remote_ac/button',controller.getButtonAC)
    router.get('/ac/:button',controller.getACRemote)
}
