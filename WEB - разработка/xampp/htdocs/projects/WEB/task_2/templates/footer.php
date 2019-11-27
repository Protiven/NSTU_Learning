		<div class="copyright_"><p class="copyr">© 2019 ООО «Новости»</p></div>
		<script src="js/jquery-3.4.1.min.js"></script>
		<script	>
		$(window).on('load', function() {
		  // действия после полной загрузки страницы...
		  alert( "Привет" );
		});
		$(document).ready(function(){
			$('.Image_news').on('click', function()
			{
				$(this).css('width', '400%');
			});		
		});
		</script>
	</body>
</html>