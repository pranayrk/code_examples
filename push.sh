current_date=$(date +"%Y%m%d_%H%M%S")
git add -A
git commit -am "$current_date" 
git push
