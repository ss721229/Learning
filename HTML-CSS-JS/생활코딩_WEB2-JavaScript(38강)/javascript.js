var Body = {
    setColor : function (color){
        $('body').css("color", color);
        // document.querySelector('body').style.color = color ;
    },
    setBackgroundColor : function (color){
        $('body').css("background-color", color);
        // document.querySelector('body').style.backgroundColor = color ;
    }
}
function setColor(color){
    var spanlist = document.querySelectorAll('span');
    // var i = 0;
    // while(i < spanlist.length)
    //     {
    //         spanlist[i].style.color = color;
    //         i+=1;
    //     }
    $('span').css("color",color);
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