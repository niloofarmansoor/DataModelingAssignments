var margin = {top: 40, right: 40, bottom: 30, left: 40};
var width = 800 - margin.left - margin.right;
var height = 400;

//the range is from 0 to width defined.
var x = d3.scale.linear().range([0, width]);

var y = d3.scale.linear().range([height, 0]);

//define the width of the chart
var chart = d3.select(".chart")
        .attr("width", width + margin.left + margin.right)
        .attr("height", height + margin.left + margin.right);

//Translate: This transform specifies a translation by x and y. If y is not provided, it is assumed to be zero.

//each bar and their margin
var allgroup = chart.append("g")
        .attr("transform", "translate(" + margin.left + "," + margin.top + ")");

//appending a text to the bars
var tooltip = chart.append("text")
        .style("visibility", "hidden");

d3.tsv("state_population_gdp.tsv", type, function(error, data) {

        y.domain([0, d3.max(data, function(d) 
                { return d.gdp; })]);

        var barWidth = width / data.length;

	var bar = allgroup.selectAll("g")
		.data(data)
                .enter()
                .append("g")
                .attr("transform", function(d, i) 
                { return "translate(" + i * barWidth + ",0)"; });

        bar.append("rect")
        .attr("y", function(d) { return y(d.gdp); })
        .attr("height", function(d) { return height - y(d.gdp); })
        .attr("width", barWidth - 1)

        .on("mouseover", function(d, i){
            var tipy = d3.select(this).attr("height");
            var tipx = barWidth * i;
            tooltip.attr("y", height - tipy + 30);
            tooltip.attr("dx", tipx+60);
            tooltip.style("visibility", "visible");
            tooltip.style("fill", "black");
            tooltip.text(d.gdp);
            d3.select(this).style("fill", "orange");})
        
        .on("mouseout", function(){
            tooltip.style("visibility", "hidden");
            d3.select(this).style("fill", "steelblue");})

});

function type(d) {
	d.gdp = +d.gdp;
	return d;
}
