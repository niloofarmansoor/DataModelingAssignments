var margin = {top: 20, right: 100, bottom: 50, left: 100};
var width = 960 - margin.left - margin.right;
var height = 400;

//the range is from 0 to width defined.
var x = d3.scale.linear().range([0, width]);
var y = d3.scale.linear().range([height, 0]);

var xAxis = d3.svg.axis()
    .scale(x)
    .orient("bottom");

var yAxis = d3.svg.axis()
    .scale(y)
    .orient("left");

//Translate: This transform specifies a translation by x and y. 
//If y is not provided, it is assumed to be zero.

var svg = d3.select("body").append("svg")
    .attr("width", width + margin.left + margin.right)
    .attr("height", height + margin.top + margin.bottom)
    .append("g")
    .attr("transform", "translate(" + margin.left + "," + margin.top + ")");

var tooltip = d3.select("svg").append("text")
        .style("visibility", "hidden");

//appending a text to the bars
d3.tsv("state_population_gdp.tsv", type, function(error, data) {

        x.domain(d3.extent(data, function(d) {return d.population;})).nice();
        y.domain(d3.extent(data, function(d) {return d.gdp;})).nice();
        
        svg.append("g")
                .attr("class", "x axis")
                .attr("transform", "translate(0," + height + ")")
                .call(xAxis)
                .append("text")
                        .attr("class", "label")
                        .attr("x", width)
                        .attr("y", -6)
                        .style("text-anchor", "end")
                        .text("population");

        svg.append("g")
                .attr("class", "y axis")
                .call(yAxis)
                .append("text")
                .attr("class", "label")
                .attr("transform", "rotate(-90)")
                        .attr("y", 6)
                        .attr("dy", ".71em")
                        .style("text-anchor", "end")
                        .text("gdp");

        
        svg.selectAll(".dot")
                .data(data)
                .enter().append("circle")
                        .attr("class", "dot")
                        .attr("r", 6)
                        .attr("cx", function(d) { return x(d.population); })
                        .attr("cy", function(d) { return y(d.gdp); })
                        .style("fill", "purple")

                        .on("mouseover", function(d, i){
                                var per_capita = d.gdp / d.population;
                                var per_capita_rounded = roundToTwo(per_capita);
                                tooltip.style("visibility", "visible");
                                tooltip.attr("x", x(d.population));
                                tooltip.attr("y", y(d.gdp));
                                //tooltip.attr("dy", 100);
                                tooltip.text(d.state + ": " + per_capita_rounded);
                                d3.select(this).style("fill", "cyan");})
        
                        .on("mouseout", function(){
                        tooltip.style("visibility", "hidden");
                        d3.select(this).style("fill", "purple");});

});

function roundToTwo(num) {    
        return +(Math.round(num + "e+2")  + "e-2");
}

function type(d) {
        d.state = d.state;
        d.population = +d.population;
        d.gdp = +d.gdp;
	return d;
}

