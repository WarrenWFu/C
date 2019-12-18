module.exports = {
  apps : [{
    name: 'FYM_NODEJS_PM2_TEST',
    cwd: '.',
    script: './main.js',

    // Options reference: https://pm2.keymetrics.io/docs/usage/application-declaration/
    //args: 'one two',
    instances: 1,
    autorestart: true,
    watch: false,
    max_memory_restart: '1G',
    exec_mode: 'fork',
    env: {
      NODE_ENV: 'development'
    },
    env_production: {
      NODE_ENV: 'production'
    }
    //node-args:''
  }],

//  deploy : {
//    production : {
//      user : 'node',
//      host : '212.83.163.1',
//      ref  : 'origin/master',
//      repo : 'git@github.com:repo.git',
//      path : '/var/www/production',
//      'post-deploy' : 'npm install && pm2 reload ecosystem.config.js --env production'
//    }
//  }
};
