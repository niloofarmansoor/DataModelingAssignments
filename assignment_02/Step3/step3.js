var margin = {top: 10, bottom: 20, right: 20, left: 20}
var width = 800 - margin.left - margin.right;
var height = 400;

var container = document.getElementById("chart_container");

document.getElementById("chart_container").style.width = width+"px";
document.getElementById("chart_container").style.height = height+"px";

var state_info = [];

var openFile = function(event) {

    var input = event.target;
    var file = input.files[0];

    var reader = new FileReader();

    //get the file's contents.
    reader.onload = function(e) {
        var text = reader.result;
        read_TSV(text);
    }
    reader.readAsText(file);
    //this tells the reader to read it as Text
}

function read_TSV(tsv){

    var lines = tsv.split("\n");

    for (var i = 1; i < lines.length-1; i++){

        var current_line = lines[i].split("\t");

        state_info[i] = {state: current_line[0], population: current_line[1], gdp: current_line[2]};
    }

    create_div(state_info);
}

function create_div(states){

    var x = margin.left;
    var bar_height_before = 0;

    for (var k = 1; k < state_info.length; k++){

        var bar_height = state_info[k].population/100000;

        if (bar_height > bar_height_before)
        {
            bar_height_before = bar_height;
        }

        var bar = document.createElement("div");
        bar.setAttribute("class", "bar");
        bar.setAttribute("id", "state"+k);
        bar.style.marginLeft = 1 + "px";
        bar.style.height = bar_height + "px";
        bar.style.marginTop = height - bar_height + 20 + "px";
        bar.style.width = 13 + "px";
        container.appendChild(bar);

    }

    document.getElementById("chart_container").style.height = bar_height_before +"px"; 

    /*var id = [];

    for (var k = 1; k < state_info.length -1; k++){

        id[k] = "state"+k;
        console.log(id);
        document.getElementById(id[k]).onmouseover = function() {mouseOver(id[k])};

    }*/

    document.getElementById("state1").onmouseover = function() {mouseOver(1)};    
    document.getElementById("state2").onmouseover = function() {mouseOver(2)};
    document.getElementById("state3").onmouseover = function() {mouseOver(3)};    
    document.getElementById("state4").onmouseover = function() {mouseOver(4)};
    document.getElementById("state5").onmouseover = function() {mouseOver(5)};    
    document.getElementById("state6").onmouseover = function() {mouseOver(6)};
    document.getElementById("state7").onmouseover = function() {mouseOver(7)};    
    document.getElementById("state8").onmouseover = function() {mouseOver(8)};
    document.getElementById("state9").onmouseover = function() {mouseOver(9)};    
    document.getElementById("state10").onmouseover = function() {mouseOver(10)};
    document.getElementById("state11").onmouseover = function() {mouseOver(11)};    
    document.getElementById("state12").onmouseover = function() {mouseOver(12)};
    document.getElementById("state13").onmouseover = function() {mouseOver(13)};    
    document.getElementById("state14").onmouseover = function() {mouseOver(14)};
    document.getElementById("state15").onmouseover = function() {mouseOver(15)};    
    document.getElementById("state16").onmouseover = function() {mouseOver(16)};
    document.getElementById("state17").onmouseover = function() {mouseOver(17)};    
    document.getElementById("state18").onmouseover = function() {mouseOver(18)};
    document.getElementById("state19").onmouseover = function() {mouseOver(19)};    
    document.getElementById("state20").onmouseover = function() {mouseOver(20)};
    document.getElementById("state21").onmouseover = function() {mouseOver(21)};    
    document.getElementById("state22").onmouseover = function() {mouseOver(22)};
    document.getElementById("state23").onmouseover = function() {mouseOver(23)};    
    document.getElementById("state24").onmouseover = function() {mouseOver(24)};
    document.getElementById("state25").onmouseover = function() {mouseOver(25)};    
    document.getElementById("state26").onmouseover = function() {mouseOver(26)};
    document.getElementById("state27").onmouseover = function() {mouseOver(27)};    
    document.getElementById("state28").onmouseover = function() {mouseOver(28)};
    document.getElementById("state29").onmouseover = function() {mouseOver(29)};    
    document.getElementById("state30").onmouseover = function() {mouseOver(30)};
    document.getElementById("state31").onmouseover = function() {mouseOver(31)};    
    document.getElementById("state32").onmouseover = function() {mouseOver(32)};
    document.getElementById("state33").onmouseover = function() {mouseOver(33)};    
    document.getElementById("state34").onmouseover = function() {mouseOver(34)};
    document.getElementById("state35").onmouseover = function() {mouseOver(35)};    
    document.getElementById("state36").onmouseover = function() {mouseOver(36)};
    document.getElementById("state37").onmouseover = function() {mouseOver(37)};    
    document.getElementById("state38").onmouseover = function() {mouseOver(38)};
    document.getElementById("state39").onmouseover = function() {mouseOver(39)};    
    document.getElementById("state40").onmouseover = function() {mouseOver(40)};
    document.getElementById("state41").onmouseover = function() {mouseOver(41)};    
    document.getElementById("state42").onmouseover = function() {mouseOver(42)};
    document.getElementById("state43").onmouseover = function() {mouseOver(43)};    
    document.getElementById("state44").onmouseover = function() {mouseOver(44)};
    document.getElementById("state45").onmouseover = function() {mouseOver(45)};    
    document.getElementById("state46").onmouseover = function() {mouseOver(46)};
    document.getElementById("state47").onmouseover = function() {mouseOver(47)};    
    document.getElementById("state48").onmouseover = function() {mouseOver(48)};
    document.getElementById("state49").onmouseover = function() {mouseOver(49)};    
    document.getElementById("state50").onmouseover = function() {mouseOver(50)};   
    document.getElementById("state51").onmouseover = function() {mouseOver(51)};

    document.getElementById("state1").onmouseout = function() {mouseOut(1)};    
    document.getElementById("state2").onmouseout = function() {mouseOut(2)};
    document.getElementById("state3").onmouseout = function() {mouseOut(3)};    
    document.getElementById("state4").onmouseout = function() {mouseOut(4)};
    document.getElementById("state5").onmouseout = function() {mouseOut(5)};    
    document.getElementById("state6").onmouseout = function() {mouseOut(6)};
    document.getElementById("state7").onmouseout = function() {mouseOut(7)};    
    document.getElementById("state8").onmouseout = function() {mouseOut(8)};
    document.getElementById("state9").onmouseout = function() {mouseOut(9)};    
    document.getElementById("state10").onmouseout = function() {mouseOut(10)};
    document.getElementById("state11").onmouseout = function() {mouseOut(11)};    
    document.getElementById("state12").onmouseout = function() {mouseOut(12)};
    document.getElementById("state13").onmouseout = function() {mouseOut(13)};    
    document.getElementById("state14").onmouseout = function() {mouseOut(14)};
    document.getElementById("state15").onmouseout = function() {mouseOut(15)};    
    document.getElementById("state16").onmouseout = function() {mouseOut(16)};
    document.getElementById("state17").onmouseout = function() {mouseOut(17)};    
    document.getElementById("state18").onmouseout = function() {mouseOut(18)};
    document.getElementById("state19").onmouseout = function() {mouseOut(19)};    
    document.getElementById("state20").onmouseout = function() {mouseOut(20)};
    document.getElementById("state21").onmouseout = function() {mouseOut(21)};    
    document.getElementById("state22").onmouseout = function() {mouseOut(22)};
    document.getElementById("state23").onmouseout = function() {mouseOut(23)};    
    document.getElementById("state24").onmouseout = function() {mouseOut(24)};
    document.getElementById("state25").onmouseout = function() {mouseOut(25)};    
    document.getElementById("state26").onmouseout = function() {mouseOut(26)};
    document.getElementById("state27").onmouseout = function() {mouseOut(27)};    
    document.getElementById("state28").onmouseout = function() {mouseOut(28)};
    document.getElementById("state29").onmouseout = function() {mouseOut(29)};    
    document.getElementById("state30").onmouseout = function() {mouseOut(30)};
    document.getElementById("state31").onmouseout = function() {mouseOut(31)};    
    document.getElementById("state32").onmouseout = function() {mouseOut(32)};
    document.getElementById("state33").onmouseout = function() {mouseOut(33)};    
    document.getElementById("state34").onmouseout = function() {mouseOut(34)};
    document.getElementById("state35").onmouseout = function() {mouseOut(35)};    
    document.getElementById("state36").onmouseout = function() {mouseOut(36)};
    document.getElementById("state37").onmouseout = function() {mouseOut(37)};    
    document.getElementById("state38").onmouseout = function() {mouseOut(38)};
    document.getElementById("state39").onmouseout = function() {mouseOut(39)};    
    document.getElementById("state40").onmouseout = function() {mouseOut(40)};
    document.getElementById("state41").onmouseout = function() {mouseOut(41)};    
    document.getElementById("state42").onmouseout = function() {mouseOut(42)};
    document.getElementById("state43").onmouseout = function() {mouseOut(43)};    
    document.getElementById("state44").onmouseout = function() {mouseOut(44)};
    document.getElementById("state45").onmouseout = function() {mouseOut(45)};    
    document.getElementById("state46").onmouseout = function() {mouseOut(46)};
    document.getElementById("state47").onmouseout = function() {mouseOut(47)};    
    document.getElementById("state48").onmouseout = function() {mouseOut(48)};
    document.getElementById("state49").onmouseout = function() {mouseOut(49)};    
    document.getElementById("state50").onmouseout = function() {mouseOut(50)};
    document.getElementById("state51").onmouseout = function() {mouseOut(51)};

}

var pop_text = document.createElement("span");

function mouseOver(s)  
{  
    var bar_height = state_info[s].population/100000;

    id = "state"+s;
    document.getElementById(id).style.backgroundColor = "red";
    
    pop_text.setAttribute("class","sr-only");
    pop_text.textContent = state_info[s].population.toString();
    pop_text.style.marginLeft = 13 * (s-1) + "px";
    container.appendChild(pop_text);
}

function mouseOut(s)  
{  
    id = "state"+s;
    document.getElementById(id).style.backgroundColor = "steelblue";
    pop_text.textContent = "";
}

