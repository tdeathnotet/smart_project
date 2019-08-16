import express from 'express'
import fs from 'fs'
import bodyParser from 'body-parser'
//import auth from './middlewere/auth'
import cookieParser from 'cookie-parser'
//import session from 'express-session'
import cors from 'cors'

function setupRoutes(app){
    const APP_DIR = `${__dirname}/app`
    const features = fs.readdirSync(APP_DIR).filter(
        file => fs.statSync(`${APP_DIR}/${file}`).isDirectory()
    )

    features.forEach(features => {
        const router = express.Router()
        const routes = require(`${APP_DIR}/${features}/routes.js`)

        routes.setup(router)
        app.use(`/${features}`, router)
    })
}

export function setup(){
    const app = express()
    const PORT = 4000

    //app.use(auth)
    app.use(express.static(__dirname + '/uploads'));
    app.use(bodyParser.urlencoded({ extended: true }))
    app.use(bodyParser.json()) 
    app.use(cookieParser())
    app.use(cors())
    setupRoutes(app)

    app.listen(PORT, () =>
    console.log('App run port' + PORT)
    )
    
}