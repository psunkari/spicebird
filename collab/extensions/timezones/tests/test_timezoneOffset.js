function validate(time1, time2, offset) {
  var hours = offset/3600;
  offset %= 3600;

  var minutes = offset/60;
  offset %= 60;

  if (time1.getHours() - time2.getHours() == hours
      && time1.getMinutes() - time2.getMinutes() == minutes)
    return true;

  return false;
}

// Test csITimezones.getTimzoneOffset
function run_test() {
  var offset = timezones.getTimezoneOffset('Australia/Brisbane');
  var curtime = new Date();
  var latime = new Date();
  latime.setTime( curtime.getTime() - offset*1000 );

  dump('curtime: ' + curtime + '\n');
  dump('latime: ' + latime.getUTCHours() + ":" + latime.getUTCMinutes() + ":" + latime.getUTCSeconds() + '\n');

  do_check_true( validate(curtime, latime, 1620 /*4.5 Hrs*/) );
}


