export class MergeSort {
  /**
   * Sorts an array using the merge sort algorithm with slice-based approach
   * @param arr - The input array to be sorted
   * @returns A new sorted array
   */

  sortWithSlice<T>(arr: T[]): T[] {
    // BAse case: If array has 1 or fewer elements, it's already sorted
    if (arr.length <= 1) {
      return arr
    }

    // Find the middle point
    const mid = Math.floor(arr.length / 2)

    // Recursively split and sort left and right halves
    const sortedLeft = this.sortWithSlice(arr.slice(0, mid))
    const sortedRight = this.sortWithSlice(arr.slice(mid))

    return this.mergeSlice(sortedLeft, sortedRight)

  }

  /**
   * Merges two sorted arrays using slice approach
   * @param left - First sorted array
   * @param right - Second sorted array
   * @returns A merged and sorted array
   */
  private mergeSlice<T>(left: T[], right: T[]): T[] {
    const result: T[] = []

    let leftIndex = 0
    let rightIndex = 0

    while (leftIndex < left.length && rightIndex < right.length){
      if (left[leftIndex] < right[rightIndex]){
        result.push(left[leftIndex])
        leftIndex++
      } else {
        result.push(right[rightIndex])
        rightIndex++
      }
    }

    // Add remaining elements from left array, if any
    return result.concat(
      left.slice(leftIndex), 
      right.slice(rightIndex)
    );

  }

  /**
   * Sorts an array in-place using merge sort algorithm
   * @param arr - The array to be sorted
   */
  sortInPlace<T>(arr: T[]) {
    const temp = Array(arr.length)
    this.mergeSortInPlace(arr, temp, 0, arr.length - 1)
  }

  /**
   * Recursive in-place merge sort implementation
   * @param arr - The array being sorted
   * @param left - Starting index of the subarray
   * @param right - Ending index of the subarray
   */
  private mergeSortInPlace<T>(arr: T[], temp: T[], left: number, right: number){
    if (left >= right) {
      return
    }
    const mid = Math.floor((left + right) / 2)
    
    this.mergeSortInPlace(arr, temp, left, mid)
    this.mergeSortInPlace(arr, temp, mid+1, right)

    this.mergeInPlace(arr, temp, left, mid, right )
  }

  private mergeInPlace<T>(arr: T[], temp: T[], left: number, mid: number, right: number) {
    let i = left
    let j = mid + 1
    let k = left

    for (let t = left; t <= right; t++) {
      temp[t] = arr[t]
    }

    while (i <= mid && j <= right) {
      if (temp[i] <= temp[j]) {
        arr[k++] = temp[i++]
      } else {
        arr[k++] = temp[j++]
      }
    }

    while (i <= mid) {
      arr[k++] = temp[i++]
    }
  }
}