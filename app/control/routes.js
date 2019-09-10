import controller from './controller'


export function setup(router){
    //________________________DECODE TV REMOTE___________________________
    router.post('/api/remote_tv',controller.addTVRemote)
    //router.get('/:id',controller.getName)  //url = http://localhost:4000/controller/mashiro
    router.get('/tv/:button',controller.getTVRemote)

    //________________________DECODE AC REMOTE___________________________
    router.post('/api/remote_ac',controller.addACRemote)
    //________________________DECODE FAN REMOTE__________________________
    // router.post('/api/remote_fan',controller.)


    //--------------------------------------------TV---------------------------------
    router.get('/remote_tv/button',controller.getButtonTV)
    router.post('/remote_tv/tv_On_post',controller.addTvOnPost)
    //--------------------------------------------FAN--------------------------------
    router.get('/remote_fan/button',controller.getButtonFan)
    router.post('/remote_tv/fan_On_post',controller.addFanOnPost)
    //-------------------------------------------AC----------------------------------
    
}
