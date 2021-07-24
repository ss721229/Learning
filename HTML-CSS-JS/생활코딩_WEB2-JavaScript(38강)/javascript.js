var Body = {
    setColor : function (color){
        document.querySelector('body').style.color = color ;
    },
    setBackgroundColor : function (color){
        document.querySelector('body').style.backgroundColor = color ;
    }
}
function setColor(color){
    var spanlist = document.querySelectorAll('span');
    var i = 0;
    while(i < spanlist.length)
        {
            spanlist[i].style.color = color;
            i+=1;
        }
}
function allBtnChange(dayOrNight) {
    var btn = document.getElementsByClassName("handlerBtn");
    /* or var btn = document.querySelectorAll('.' + self.className); */
    for(var i = 0 ; i < btn.length ; i++)
        btn[i].value = dayOrNight;
}
function nightDayHandler(self){
    if(self.value === 'Night') {
        Body.setBackgroundColor('black');
        Body.setColor('white');
        allBtnChange('Day');
        setColor('powderblue');

    } else {
        Body.setBackgroundColor('white');
        Body.setColor('black');
        allBtnChange('Night');
        setColor('blue');
    }
}