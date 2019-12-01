/*$(window).on('load', function() {
    // действия после полной загрузки страницы...
    alert( "Привет" );
});
$(document).ready(function(){
    $('.Image_news').on('click', function()
    {
        $(this).css('width', '400%');
    });		
});


$( "p" ).click(function() {
    var htmlString = $( this ).html();
    $( this ).text( htmlString );
});

Image_news_1
*/
		
$(document).ready(function(){
    $('.Image_news').click(function() 
    {
        var $image = $('#hidden_im');
        var $element = $('#hidden_el');
        $element.css('opacity', '1');
        $element.css('z-index', '9999999');
        
        $image.css('width', '100%');
        $image.attr("src", $(this).attr("src"));
    });	

    
    $('#hidden_el').click(function()
    {
        var $element = $('#hidden_el');
        $element.css('opacity', '0');
        $element.css('z-index', '-3');
    });	
});